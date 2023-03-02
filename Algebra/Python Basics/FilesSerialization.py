### FILES ###

# data stream: any source of input data or a destination to output data
# standard: sys.stdin & sys.stdout

# formatted (.txt, .py) or unformatted (.jpg, .docx, .pdf...)
# mode r -> error if the file doesn't exist; w+ (read/overwrite/create), a+ (read/append/creates)
# mode rb, wb, a+b... -> reads binary
""" f = open("text.txt", mode = "w+", encoding = "utf-8")

s = f.read()        # whole file
s = f.read(10)      # 10 bytes
s = f.readline()
l = f.readlines()   # file into a list of rows
f.write(s)          # writes a string
f.writelines(l)     # writes all strings from list l

f.write(f"{2:5d}\n")    # 4 indentations before writing
s.find("string")        
s.strip()               # removes leading/trailing characters """

### SERIALIZATION ###

# binary format (pickle module): f = open("pickle.bin", "wb")

#  if an object is serialized with pickle protocol of version X, 
#  it can only be deserialized with pickle protocol of the same version

""" import pickle
obj = ["string1", "string2", "string3"]
try: 
    pickle.dump(obj, f);        # serializes obj and writes pickle obj into f
    data=pickle.dumps(obj);     # serializes obj and returns pickle obj
    data=pickle.load(f)         # returns deserialized pickle object from f
    data=pickle.loads(obj)      # returns deserialized pickle object obj
except EOFError:
    pass
except pickle.UnpicklingError as e:
    print(e)

# JSON: {} -> key/value container, [] -> list, "..." -> string, null
# same methods as for pickle above

# CSV: Comma Separated Values; for tabular data
import csv
csv.writer(f, delimiter = ';')
csv.writerow(s)           # writes an iterable object (loop)
csv.reader(f, delimiter = ';', newline = "")

f.close()
 """

import csv 
data = [        # always use this to write csv, [['1', '2', '3'], [4, 5, 6], [7, 8, 9], [None, 0, None]]
  [1,2,3],
  [4,5,6],
  [7,8,9],
  [None,0,None]
]

# with block: automatic data closing
with open("points.csv", "w", newline="") as f:
  csv_writer = csv.writer(f, delimiter=";")     # tocka-zarez stavlja svaki broj u svoju celiju, obican zarez stavlja u jednu celiju 1,2,3
  for row in data:
    csv_writer.writerow(row)
