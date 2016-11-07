#!/usr/bin/python

import os, sys
import os.path

def fileEditor(mainStr, infoLine):
	if infoLine[0] == "B":
		#strip the Bold tag from .info
		eraseB = infoLine.strip("B ")
		#mainTemp holds the variable to be used in the last step
		mainTemp = eraseB
		#format the string with the tags
		eraseB = "<B>%s</B>" % eraseB
		#manipulate and then return the string from main file
		mainStr = mainStr.replace(mainTemp, eraseB)
	elif infoLine[0] == "U":			
		eraseB = infoLine.strip("U ")
		mainTemp = eraseB
		eraseB = "<U>%s</U>" % eraseB
		mainStr = mainStr.replace(mainTemp, eraseB)

	elif infoLine[0] == "I":
		eraseB = infoLine.strip("I ")
		mainTemp = eraseB
		eraseB = "<I>%s</I>" % eraseB
		mainStr = mainStr.replace(mainTemp, eraseB)
	else:
		return NULL

	return mainStr

# open a fifo queue for writing, write 10 strings, close fifo
# sends text through a fifo queue to the reader program
if __name__ == "__main__":
	#this q1 is to open and read the lines of the file
	fpContent = "./files/q1"
	pipe = open(fpContent, "r")
	line = pipe.readlines()
	os.remove(fpContent)
	

	writeToC = str(sys.argv[2])
	writeFile = os.open("./files/"+writeToC, os.O_WRONLY)

	os.write(writeFile, "<HTML>")
	os.write(writeFile, "\n\n")
	os.write(writeFile, "<HEAD>")
	os.write(writeFile, "\n")
	os.write(writeFile, "<TITLE>")
	os.write(writeFile, sys.argv[3][8:len(sys.argv[3])])
	os.write(writeFile, "</TITLE>")
	os.write(writeFile, "\n")
	os.write(writeFile, "</HEAD>")
	os.write(writeFile, "\n")
	os.write(writeFile, "\n")

	os.write(writeFile, "<BODY>")
	os.write(writeFile, "\n")

	infoFileName = str(sys.argv[3]) + ".info"

	if os.path.isfile(infoFileName):
		with open(infoFileName) as infoFp:
			infoList = []
			for infoLine in infoFp:
				infoList.append(infoLine)
		for piece in line:
			flag = 0
			for infoLine in infoList:	
				if piece.find(infoLine[2:len(infoLine)-1]) != -1:
					flag = 1		
					edittedStr = fileEditor(piece, infoLine[:-1])
					os.write(writeFile, edittedStr)
					break
			if flag != 1:
				os.write(writeFile, piece)
	else:
		for piece in line:
			os.write(writeFile, piece)

	os.write(writeFile, "</BODY>")
	os.write(writeFile, "\n")
	os.write(writeFile, "\n")
	os.write(writeFile, "</HTML>")
	os.write(writeFile, "\n") 
	os.close(writeFile)
