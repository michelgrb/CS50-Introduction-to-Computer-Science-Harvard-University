import cs50

# lower beacause of only 1 array with small letters
text = str.lower(cs50.get_string(("Text:")))

# len of text
tlen = int(len(text)) - 1

alph = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
        "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]

end = ["!", ".", "?"]

# needed variables
lettercount = 0
wordcount = 0
sencount = 0

for i in range(tlen+1):

    if text[i] in alph:
        lettercount += 1
    elif text[i] == " ":
        wordcount += 1
    elif text[i] in end:
        sencount += 1

wordcount += 1

# calcs
l = (lettercount / wordcount) * 100
s = (sencount / wordcount) * 100

x = round(0.0588 * l - 0.296 * s - 15.8)

# for special cases
if x >= 16:
    x = "16+"
    print("Grade", x)
elif x < 1:
    print("Before Grade 1")
else:
    print("Grade", x)