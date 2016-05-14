#encoding=utf-8
import jieba
import jieba.posseg as pseg
import MySQLdb
import math
import sys

reload(sys)
sys.setdefaultencoding('utf8')

def get_product():
  try:
    conn = MySQLdb.connect(host='host',user='user',passwd='passwd',db='db',charset="utf8") # fill in info
    cur = conn.cursor()
    #cur.execute('select product_id, cate2 from product limit 2')
    cur.execute('')
    data = cur.fetchall()
    cur.close()
    conn.close()
    return data
  except MySQLdb.Error,e:
    return null

def get_review():
  try:
    conn = MySQLdb.connect(host='host',user='user',passwd='passwd',db='db',charset='utf8')
    cur = conn.cursor()
    command = '''select review_word from review_index where product_id 
      in (select product_id from (select product_id, count(*) as cnt from review_index where product_id 
      in (select product_id from product where cate2="运动鞋") 
      group by product_id) as A where cnt > 100)'''
    cur.execute(command)
    data = cur.fetchall()
    cur.close()
    conn.close()
    return data
  except MySQLdb.Error,e:
    print "sqldb error"
    return null

def remove_all(the_list, val):
   return [value for value in the_list if value != val]

def cut_review(review):
  #seg_list = jieba.cut("|很漂亮，我很喜欢，同事看了也说漂亮。|||",cut_all=False)
  #print "Default Mode:", "/ ".join(seg_list) #精确模式
  clean_list = list(jieba.cut(review ,cut_all=False))
  return remove_all(clean_list, "|")

def extract_candidates(review):
  opinions = set()
  features = set()
  words = pseg.cut(review)
  for w in words:
    if (w.flag == "v") or (w.flag == "a"):
      opinions.add(w.word)
      #print w.word
    elif (w.flag == "n"):
      features.add(w.word)
      #print w.word
  return [opinions, features]

def ffth():
  return 38.0
def foth():
  return 38.0
def ooth():
  return 38.0

def L(p, k, n_k):
  return pow(p,k) * pow(1-p, n_k)

def associate_score(ab, a_b, _ab, _a_b): # k1=ab, k2=a_b, k3=_ab, k4+_a_b
  return 2*(math.log(L(float(ab)/(ab+_ab), ab, _ab), math.e) \
          + math.log(L(float(a_b)/(a_b+_a_b), a_b, _a_b), math.e) \
          - math.log(L(float(ab+a_b)/(ab+a_b+_ab+_a_b), ab, _ab), math.e) \
          - math.log(L(float(ab+a_b)/(ab+a_b+_ab+_a_b), a_b, _a_b), math.e))

if __name__ == '__main__':
  cnt_opinions = {}
  cnt_features = {}
  joins_oo = {}
  joins_of = {}
  joins_ff = {}
  candidate_opinions = set()
  candidate_features = set()

  #products = get_product()
  #for product in products:
  review_words = get_review()
  for review_word in review_words:
    print review_word
  print "db fetching completed"
  total = len(review_words)

  for review_word in review_words:
    #review_cut_list = cut_review(review_word)
    #print "/ ".join(review_cut_list) #精确模式

    [os, fs] = extract_candidates(review_word[0])
    candidate_opinions.update(os)
    candidate_features.update(fs)

    for o in os:
      if cnt_opinions.get(o) is None:
        cnt_opinions[o] = 1
      else:
        cnt_opinions[o] = cnt_opinions[o] + 1
      for o2 in os:
        if o != o2:
          oo = o + "|" + o2
          if joins_oo.get(oo) is None:
            joins_oo[oo] = 1
          else:
            joins_oo[oo] = joins_oo[oo] + 1
      for f in fs:
        of = o + "|" + f
        if joins_of.get(of) is None:
          joins_of[of] = 1
        else:
          joins_of[of] = joins_of[of] + 1
    for f in fs:
      if cnt_features.get(f) is None:
        cnt_features[f] = 1
      else:
        cnt_features[f] = cnt_features[f] + 1
      for f2 in fs:
        if f != f2:
          ff = f + "|" + f2
          if joins_ff.get(ff) is None:
            joins_ff[ff] = 1
          else:
            joins_ff[ff] = joins_ff[ff] + 1
  print "association data collected"


  opinions = set()
  features = set(unicode("鞋",'utf8')) #Seeds

  while (1):
    new_opinions = []
    new_features = []
    for o in opinions:
      for co in candidate_opinions:
        oo = o + "|" + co
        if joins_oo.get(oo) is None:
          joins_oo[oo] = 0
        if (associate_score(joins_oo[oo], cnt_opinions[o]-joins_oo[oo], cnt_opinions[co]-joins_oo[oo], total+joins_oo[oo]-cnt_opinions[o]-cnt_opinions[co]) >= ooth()):
          new_opinions.append(co)
      for cf in candidate_features:
        of = o + "|" + cf
        if joins_of.get(of) is None:
          joins_of[of] = 0
        if (associate_score(joins_of[of], cnt_opinions[o]-joins_of[of], cnt_features[cf]-joins_of[of], total+joins_of[of]-cnt_opinions[o]-cnt_features[cf]) >= foth()):
          new_features.append(cf)
    for f in features:
      for co in candidate_opinions:
        of = co + "|" + f
        if joins_of.get(of) is None:
          joins_of[of] = 0
        if (associate_score(joins_of[of], cnt_opinions[co]-joins_of[of], cnt_features[f]-joins_of[of], total+joins_of[of]-cnt_opinions[co]-cnt_features[f]) >= foth()):
          new_opinions.append(co)
      for cf in candidate_features:
        ff = f + "|" + cf
        if joins_ff.get(ff) is None:
          joins_ff[ff] = 0
        if (associate_score(joins_ff[ff], cnt_features[f]-joins_ff[ff], cnt_features[cf]-joins_ff[ff], total+joins_ff[ff]-cnt_features[f]-cnt_features[cf]) >= ffth()):
          new_features.append(cf)
    candidate_opinions.difference_update(new_opinions)
    candidate_features.difference_update(new_features)
    opinions.update(new_opinions)
    features.update(new_features)
    if (len(new_features) == 0) and (len(new_opinions) == 0):
      break;
    #print candidate_opinions
    #print candidate_features
    #print opinions
    #print features
  for feature in features:
    print feature
  print "=============================================="
  for opinion in opinions:
    print opinion
