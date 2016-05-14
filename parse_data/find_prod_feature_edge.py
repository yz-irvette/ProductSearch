#encoding=utf-8
import csv
import jieba
import jieba.posseg as pseg
import operator
import sys

reload(sys)
sys.setdefaultencoding('utf8')

if __name__ == '__main__':
  fo = {}
  result = {}
  signal = "，。？；！|,.?;!"
  id = 0

  csvfile=file('../data/product/bag.csv','rb') # product file path
  reader = csv.reader(csvfile)
  for line in reader:
    if (line[0] != id):
      for f in fo:
        if fo[f] > 20:
          print str(id) + "|" + f + "," + str(float(fo[f])/20)
      fo = {}
      id = line[0]
    words = pseg.cut(line[4])
    prev4 = None
    prev3 = None
    prev2 = None
    prev1 = None
    for w in words:
      split = True;
      if split and (prev1 is not None):
        if prev1.word in signal:
          split = False;
        elif (prev1.flag == "n") and ((w.flag == "v") or (w.flag == "a")):
          combine = w.word + "|" + prev1.word
          if fo.get(combine) is None:
            fo[combine] = 1
          else:
            fo[combine] = fo[combine] + 1
        elif (w.flag == "n") and ((prev1.flag == "v") or (prev1.flag == "a")) and (prev2 is None or (prev2 != "不" and prev2 != "没")):
          combine = prev1.word + "|" + w.word
          if fo.get(combine) is None:
            fo[combine] = 1
          else:
            fo[combine] = fo[combine] + 1
      if split and (prev2 is not None):
        if prev2.word in signal:
          split = False;
        elif (prev2.flag == "n") and ((w.flag == "v") or (w.flag == "a")) and prev1 != "不" and prev1 != "没":
          combine = w.word + "|" + prev2.word
          if fo.get(combine) is None:
            fo[combine] = 1
          else:
            fo[combine] = fo[combine] + 1
        elif (w.flag == "n") and ((prev2.flag == "v") or (prev2.flag == "a")) and (prev3 is None or (prev3 != "不" and prev3 != "没")):
          combine = prev2.word + "|" + w.word
          if fo.get(combine) is None:
            fo[combine] = 1
          else:
            fo[combine] = fo[combine] + 1
      if split and (prev3 is not None):
        if prev3.word in signal:
          split = False;
        elif (prev3.flag == "n") and ((w.flag == "v") or (w.flag == "a")) and prev1 != "不" and prev1 != "没":
          combine = w.word + "|" + prev3.word
          if fo.get(combine) is None:
            fo[combine] = 1
          else:
            fo[combine] = fo[combine] + 1
        elif (w.flag == "n") and ((prev3.flag == "v") or (prev3.flag == "a")) and (prev4 is None or (prev4 != "不" and prev4 != "没")):
          combine = prev3.word + "|" + w.word
          if fo.get(combine) is None:
            fo[combine] = 1
          else:
            fo[combine] = fo[combine] + 1
      prev4 = prev3
      prev3 = prev2
      prev2 = prev1
      prev1 = w
  csvfile.close()
  
