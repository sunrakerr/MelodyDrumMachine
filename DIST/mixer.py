from playsound import playsound
import multiprocessing
import time
import sys

def kick_(track):
	for k in range(loop):
		for j in range(8):
			if track[0][j] == '1':
				playsound(kick)

			else:
				playsound(silence)

def snare_(track):
	for s in range(loop):
		for k in range(8):
			if track[1][k] == '1':
				playsound(snare)

			else:
				playsound(silence)

def hat_(track):
	for h in range(loop):
		for l in range(8):
			if track[2][l] == '1':
				playsound(hat)

			else:
				playsound(silence)


def clap_(track):
	for c in range(loop):
		for m in range(8):
			if track[3][m] == '1':
				playsound(clap)

			else:
				playsound(silence)

def tom_(track):
	for t in range(loop):
		for n in range(8):
			if track[4][n] == '1':
				playsound(tom)

			else:
				playsound(silence)

def bell_(track):
	for b in range(loop):
		for o in range(8):
			if track[5][o] == '1':
				playsound(bell)

			else:
				playsound(silence)

def sfx1_(track):
	for f1 in range(loop):
		for p in range(8):
			if track[6][p] == '1':
				playsound(sfx1)

			else:
				playsound(silence)

def sfx2_(track):
	for f2 in range(loop):
		for q in range(8):
			if track[7][q] == '1':
				playsound(sfx2)

			else:
				playsound(silence)

loop=10;
if int(sys.argv[1])!=-1:
        loop=int(sys.argv[1]);
kick='soundpack/Kick.wav'
snare='soundpack/Snare.wav'
hat='soundpack/Hat.wav'
clap='soundpack/Clap.wav'
tom='soundpack/Tom.wav'
bell='soundpack/Bell.wav'
sfx1='soundpack/Sfx1.wav'
sfx2='soundpack/Sfx2.wav'
silence='soundpack/Silence.wav'

track=[]
mel_file=open('example.mel','r')
for x in mel_file.readlines():
	track.append(x.replace('\n','').split(' '));



if __name__ == '__main__':

	kicker=multiprocessing.Process(target=kick_,args=[track])
	snarer=multiprocessing.Process(target=snare_,args=[track])
	hater=multiprocessing.Process(target=hat_,args=[track])
	clapper=multiprocessing.Process(target=clap_,args=[track])
	tommer=multiprocessing.Process(target=tom_,args=[track])
	beller=multiprocessing.Process(target=bell_,args=[track])
	sfx1er=multiprocessing.Process(target=sfx1_,args=[track])
	sfx2er=multiprocessing.Process(target=sfx2_,args=[track])


	kicker.start()
	snarer.start()
	hater.start()
	clapper.start()
	tommer.start()
	beller.start()
	sfx1er.start()
	sfx2er.start()

	kicker.join()
	snarer.join()
	hater.join()
	clapper.join()
	tommer.join()
	beller.join()
	sfx1er.join()
	sfx2er.join()
