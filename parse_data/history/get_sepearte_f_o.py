#encoding=utf-8
import csv
import jieba
import jieba.posseg as pseg
import operator
import sys

reload(sys)
sys.setdefaultencoding('utf8')

def get_review():
  review_words = []
  csvfile=file('shoe.csv','rb')
  reader = csv.reader(csvfile)
  for line in reader:
    review_words.append(line[4])
  csvfile.close()
  return review_words

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
    elif (w.flag == "n"):
      features.add(w.word)
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
  total = len(review_words)

  for review_word in review_words:
    #review_cut_list = cut_review(review_word)
    #print "/ ".join(review_cut_list) #精确模式
    [os, fs] = extract_candidates(review_word)
    #candidate_opinions.update(os)
    #candidate_features.update(fs)

    for o in os:
      if cnt_opinions.get(o) is None:
        cnt_opinions[o] = 1
      else:
        cnt_opinions[o] = cnt_opinions[o] + 1
    for f in fs:
      if cnt_features.get(f) is None:
        cnt_features[f] = 1
      else:
        cnt_features[f] = cnt_features[f] + 1

  sorted_features = sorted(cnt_features.items(), key=operator.itemgetter(1))
  with open('shoe_feature.csv','w') as output_f:
    output = csv.writer(output_f)
    output.writerows(sorted_features)
  sorted_opinions = sorted(cnt_opinions.items(), key=operator.itemgetter(1))
  with open('shoe_opinion.csv','w') as output_o:
    output = csv.writer(output_o)
    output.writerows(sorted_opinions)
  
  
