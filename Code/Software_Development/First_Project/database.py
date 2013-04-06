#from flask import Flask

import shelve


def makeAuth():
    """
    Takes students.dat as a parameter, makes a shelve named 'authen'.
    The keys are emails, the items are lists with [first,last,idnum,group].
    Used to authenticate login.
    """
    auth = shelve.open("authen")
    f = open("students.dat").readlines()
    for item in f:
        item = item.strip()
        email,last,first,idnum,cl,sect,pd,group = item.split(",")
        auth[email] = [first,last,idnum,group]
        #print email
        #print auth[email]

    pass
                
    

def fixNames():
    """
    Takes 'questions.txt' and 'p1.dat'.
    Creates shelve 'questions.dat'
    This shelve has keys as emails.
    The emails refer to a list.
    At each index of the list there is a list of ratings refering to that question.
    """
    
    quest = shelve.open("questions.dat")
    f = open("p1.txt").readlines()

    if len(quest) != 0:
        pass
     
    for item in f:
        item = item.strip()
        a,b = item.split(",",1)
        c = b.split(",")
        for item in c:
            quest[item] = {}
 
    quest.close()
    pass
    

def createGroups():
    """
    Makes the Groups shelve

    Entire group is referenced by the key -- so when we do the list to show who is in the group, just make sure to take out the email that is the key.
    """
    groups = shelve.open("groups")
    f = open("p1.txt").readlines()
    num = 0
    for item in f:
        item = item.strip()
        a,b = item.split(",",1)
        c = b.split(",")
        for item in c:
            groups[item] = c

    groups.close()
    pass



def getRatings(email):
    """
    Returns all the ratings of a given email in a list of lists of ratings.
    """
    quest = shelve.open("questions.dat")
    d = []
    for item in quest[email]:
        d.append(quest[email][item])
    return d

    
def addRating(rater,ratee,ratings):
    """
    Adds a rating to a person.  If a person has rated this person before it overwrites the previous rating.  Returns the ratings added.
    """
    quest = shelve.open("questions.dat", writeback = True)
    groups = shelve.open("groups")
    if not(ratee in groups[rater]):
        return "This person is not in your group, so you cannot rate them"

    quest[ratee][rater] = ratings
        
    quest.close()
    groups.close()
    
    return ratings

def getGroupMembers(email):
    """
    Returns a list of the group members of the email given.
    """
    group = shelve.open("groups")
    lis = group[email]
    lis.remove(email)
    return lis

def reset():
    """
    This function can be called to reset all ratings.
    """
    createGroups()
    fixNames()
    makeAuth()


def getPrevRatings(email):
    d = dict()
    quest = shelve.open("questions.dat")
    for item in quest:
        for ee in quest[item]:
            if ee == email:
                d[item] = quest[item][ee]
    return d



print getPrevRatings('batya.zamansky@gmail.com')
    

#print getGroupMembers('jpengsmail@gmail.com')
#print getRatings('jpengsmail@gmail.com')
#addRating('batya.zamansky@gmail.com','jpengsmail@gmail.com',[2,3,4,5,6])
#addRating('darylsew@gmail.com','jpengsmail@gmail.com',[3,4,1,8,25])
