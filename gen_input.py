from random import randint as random
pages = [random(1,10) for i in range(300)]
words = ['algorithm','thisisareallylongword','[binary search tree]','[another search phrase]','thisisareallyrealllongword','tree','heap','[heap tree]','[phrased phrase]']
f = open("large_input","w")
for page in pages:
    f.write('<'+str(page)+'>\n')
    num_lines=random(1,20)
    words_per_line=random(1,4)
    for i in range(num_lines):
        line_buf = ''
        for j in range(words_per_line):
            line_buf += words[random(0,len(words)-1)] + " "
        f.write(line_buf[:-1]+'\n')

f.write('<-1>\n')
f.close()

