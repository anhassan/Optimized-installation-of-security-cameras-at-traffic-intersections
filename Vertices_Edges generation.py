from __future__ import print_function
import re
import pprint
import sys

Street = {}
Verticesd={}
Vertices = []
intersection=[]
lwithintersect=[]
points=[]
sortedpoints=[]
Edges = []
sedge=[]
count=0

def main():
	while True:
		#Getting Input
		try:
			line = raw_input("")
		except:
			continue
		if line == "":
			#print ("Quit",end='')
			exit()
		#Getting Command
		command = line[0]
		# Getting name of Street
		stname = str(re.findall(r'"([^"]*)"', line[2:])).upper()
		if command == 'a' or  command =='r' or command == 'c':
			if len(stname) <1:
				print ("Error:Name of Street is missing")
				main()
			#Add Street
			if command == 'a':
				if stname not in Street:
					add_street(stname,line)
				else:
					print ("Error:This street already exist")
					main()
					
			#Deleting Streets
			if command == 'r':
				if stname in Street:
					del Street[stname]
				else:
					print("Error:This street doesnot exist")
					main()

			#Changing existing Streets	
			if command == 'c':
				if stname in Street:
					del Street[stname]
					add_street(stname,line)
				else:
					print ('Error:This street doesnot exist')
					main()
		#Create Graph and Edges
		elif command == 'g':
			Verticesd.clear()		 
			del Vertices[:]
			del Edges[:]
			createVertices()
			intersect()

			for i in range(0,len(Vertices)):
				Verticesd.update({i+1:Vertices[i]})
			sys.stdout.write("V %d\n" %len(Vertices))
			
			sys.stdout.write ("E {")
			for i in range(0,len(Edges)):
				#if you want to print edges in coordinate form:print "<",Edges[i][0],",",Edges[i][1],">"
				for key1,value in Verticesd.items()	 :
					if Edges[i][0]==value:
						for key2,value in Verticesd.items():
							if Edges[i][1]==value:
								if i==len(Edges)-1:
									#print ("<",key1,",",key2,">",end='')
									sys.stdout.write ("<%d" %key1)
									sys.stdout.write (",%d" %key2)
									if(i != len(Edges)-1):
										sys.stdout.write( ">,")
									else:
										sys.stdout.write( ">")
								else:
									#print ("<",key1,",",key2,">",end='')
									sys.stdout.write ("<%d" %key1)
									sys.stdout.write (",%d" %key2)
									if(i != len(Edges)-1):
										sys.stdout.write( ">,")
									else:
										sys.stdout.write( ">")
			sys.stdout.write ("}\n")
			sys.stdout.flush()
		else:
			print ('Error: You have can only enter a,c,r and g')
			main()
#Adding street and coordinates
def add_street(name,line):
	Street[name] = {}
	Street[name]["point"] = []
	n="("
	Allcoords = line[line.find(n):]
	CoordList = Allcoords.split(' ')
	coordwbracket = Allcoords.split(')(')
	if len(CoordList)>1:
		for coord in CoordList:
			try:
				cordsplited=re.findall(r'([0-9]+)',coord)
				x = float(cordsplited[0])
				y = float(cordsplited[1])
				xy = (x,y)
				Street[name]["point"].append(xy)
			except:
				print("Error:Coordinates are not entered properly")
				del Street[name]
				main()
	elif len(coordwbracket)>1:
		for coord in coordwbracket:
			try:
				cordsplited=re.findall(r'([0-9]+)',coord)
				x = float(cordsplited[0])
				y = float(cordsplited[1])
				xy = (x,y)
				Street[name]["point"].append(xy)
			except:
				print("Error:Coordinates are not entered properly")
				del Street[name]
				main()
	for name in Street:
		Street[name]["lines"]=[]
		for i in range (0,len(Street[name]["point"])-1):
			Street[name]["lines"].append([Street[name]["point"][i],Street[name]["point"][i+1]])
	return None 
#Creating vertices
def createVertices():
	for street in Street:
		for line in range(0,len(Street[street]["lines"])):
			findintersection(line,street)

	return None
#Finding Intersection
def findintersection(l,st):
	key = 1
	p1 = Street[st]["lines"][l][0]
	p2 = Street[st]["lines"][l][1]
	x1, y1 = p1[0], p1[1]
	x2, y2 = p2[0], p2[1]
	
	for street in Street:
		for line2 in range(0,len(Street[street]["lines"])):
			if st != street:
				p3 = Street[street]["lines"][line2][0]
				p4 = Street[street]["lines"][line2][1]
				x3, y3 = p3[0], p3[1]
				x4, y4 = p4[0], p4[1]
				
				xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
				xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
				ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
				yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
				
				if xnum==0 and ynum==0 and xden==0 and yden==0 : #overlapping streets
					if (x1,y1) not in Vertices:	Vertices.append((x1,y1))
					if (x1,y1) not in sedge:	sedge.append((x1,y1))
					if (x2,y2) not in Vertices:	Vertices.append((x2,y2))
					if (x2,y2) not in sedge:	sedge.append((x2,y2))
					if (x3,y3) not in Vertices:	Vertices.append((x3,y3))
					if (x3,y3) not in sedge:	sedge.append((x3,y3))
					if (x4,y4) not in Vertices:	Vertices.append((x4,y4))
					if (x4,y4) not in sedge:	sedge.append((x4,y4))
					sortedsedge= sorted(sedge , key=lambda k: [k[0], k[1]])
					if (sortedsedge[0],sortedsedge[1]) not in Edges: 
						Edges.append((sortedsedge[0],sortedsedge[1]))
					if (sortedsedge[1],sortedsedge[2]) not in Edges: 
						Edges.append((sortedsedge[1],sortedsedge[2]))
				    #if (sortedsedge[2],sortedsedge[3]) not in Edges: 
					#	Edges.append((sortedsedge[2],sortedsedge[3]))
					del sedge[:]
				if xden == 0 or yden == 0:
					continue
				elif (max(x1,x2) < min(x3,x4)): #no mutual abcisses
					continue
				elif (max(y1,y2) < min(y3,y4)): #same on y-axis
					continue
				else:
					xc = xnum / xden
					yc = ynum / yden
					if (xc < max(min(x1,x2),min(x3,x4))) or (xc > min(max(x1,x2),max(x3,x4))):
						continue
					elif (yc < max(min(y1,y2),min(y3,y4))) or (yc > min(max(y1,y2),max(y3,y4))):
						continue
					else:
						if (xc,yc) not in Vertices: Vertices.append((xc,yc))
						if (xc,yc) not in intersection: intersection.append((xc,yc))
						if (x1,y1) not in Vertices:	Vertices.append((x1,y1))
						if (x2,y2) not in Vertices:	Vertices.append((x2,y2))
						if (x3,y3) not in Vertices:	Vertices.append((x3,y3))
						if (x4,y4) not in Vertices:	Vertices.append((x4,y4))
						if ((x1,y1),(x2,y2)) not in lwithintersect: lwithintersect.append(((x1,y1),(x2,y2)))
						if ((x3,y3),(x4,y4)) not in lwithintersect: lwithintersect.append(((x3,y3),(x4,y4)))
						
						if ((x1,y1),(xc,yc)) not in Edges: Edges.append(((x1,y1),(xc,yc)))
						if ((x2,y2),(xc,yc)) not in Edges: Edges.append(((x2,y2),(xc,yc)))
						if ((x3,y3),(xc,yc)) not in Edges: Edges.append(((x3,y3),(xc,yc)))
						if ((x4,y4),(xc,yc)) not in Edges: Edges.append(((x4,y4),(xc,yc)))
						else:
							continue
			else:
				continue
	return None
#Making edges between street intersection and removing unwanted edges
def intersect():
	
	for i in range (0,len(lwithintersect)):
		#create equation
		del points[:]
		x1=lwithintersect[i][0][0]
		y1=lwithintersect[i][0][1]
		x2=lwithintersect[i][1][0]
		y2=lwithintersect[i][1][1]
		count=0	
		for w in range (0,len(Vertices)):
			x=Vertices[w][0]
			y=Vertices[w][1]
			if (x2 <= x <= x1) or (x1 <= x <= x2):
				l=int((y-y1)*(x2-x1))
				r=int((y2-y1)*(x-x1))
			
				if(l==r):
					count +=1
					if (x1,y1) not in points: points.append((x1,y1))
					if (x2,y2) not in points: points.append((x2,y2))
					if (x,y) not in points: points.append((x,y))
				elif(l!=r):
					continue
			else:
				continue
		if count >= 3:
			sortedpoints= sorted(points , key=lambda k: [k[0], k[1]]) 
			for o in range (0,len(sortedpoints)-1):
				x1=sortedpoints[o][0]
				y1=sortedpoints[o][1]
				x2=sortedpoints[o+1][0]
				y2=sortedpoints[o+1][1]
				if ((x1,y1),(x2,y2)) not in Edges: 
					if ((x2,y2),(x1,y1)) not in Edges:
						Edges.append(((x1,y1),(x2,y2)))
			for z in range (0,len(sortedpoints)-2):
				x1=sortedpoints[z][0]
				y1=sortedpoints[z][1]
				for u in range(0,len(sortedpoints)-2-z):
					x2=sortedpoints[z+u+2][0]
					y2=sortedpoints[z+u+2][1]
					f=(x1,y1),(x2,y2)
					g=(x2,y2),(x1,y1)
					if ((x1,y1),(x2,y2)) in Edges:
						Edges.remove(f)
					elif ((x2,y2),(x1,y1)) in Edges:
						Edges.remove(g)
			for (x,y) in Edges:
				if x==y:
					Edges.remove((x,y))
	return None
if __name__ == "__main__":
	main()

