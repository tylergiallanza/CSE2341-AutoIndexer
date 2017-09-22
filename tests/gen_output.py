f = open('large_input')

dictionary = {}

lineNum = 0
for line in f.readlines():
    if lineNum==-1:
        break
    if line[0] == '<':
        lineNum = int(line[1:-2])
    else:
        for word in line.split(' '):
            if word in dictionary:
                if lineNum not in dictionary[word]:
                    dictionary[word].append(lineNum)
            else:
                dictionary[word] = [lineNum]
for key, val in dictionary.iteritems():
    print(key," ",val)
f.close()
