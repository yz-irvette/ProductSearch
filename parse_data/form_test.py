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

  csvfile=file('bag.csv','rb')
  reader = csv.reader(csvfile)
  for line in reader:
    if line[3] is not "5":
      continue
    words = pseg.cut(line[4])
    output = line[0] + ","
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
          output = output + " " + w.word + "|" + prev1.word
        elif (w.flag == "n") and ((prev1.flag == "v") or (prev1.flag == "a")) and (prev2 is None or (prev2 != "不" and prev2 != "没")):
          output = output + " " + prev1.word + "|" + w.word
      if split and (prev2 is not None):
        if prev2.word in signal:
          split = False;
        elif (prev2.flag == "n") and ((w.flag == "v") or (w.flag == "a")) and prev1 != "不" and prev1 != "没":
          output = output + " " + w.word + "|" + prev2.word
        elif (w.flag == "n") and ((prev2.flag == "v") or (prev2.flag == "a")) and (prev3 is None or (prev3 != "不" and prev3 != "没")):
          output = output + " " + prev2.word + "|" + w.word
      if split and (prev3 is not None):
        if prev3.word in signal:
          split = False;
        elif (prev3.flag == "n") and ((w.flag == "v") or (w.flag == "a")) and prev1 != "不" and prev1 != "没":
          output = output + " " + w.word + "|" + prev3.word
        elif (w.flag == "n") and ((prev3.flag == "v") or (prev3.flag == "a")) and (prev4 is None or (prev4 != "不" and prev4 != "没")):
          output = output + " " + prev3.word + "|" + w.word
      prev4 = prev3
      prev3 = prev2
      prev2 = prev1
      prev1 = w
    if output[len(output) - 1] is not ',':
      print output
  csvfile.close()
  
