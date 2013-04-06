import shelve
import database


auth = shelve.open("authen")
print auth["jpengsmail@gmail.com"]

#groups = shelve.open("groups")
#print groups["fallenpwr@gmail.com"]

#print database.getRatings("jpengsmail@gmail.com")
"""
f =  open("questions.txt", "r").readlines()0

print f[0].strip()
print f[0]
"""
#print database.getGroupMembers("darylsew@gmail.com")

#database.addRating("jpengsmail@gmail.com", "darylsew@gmail.com", [5, 4, 3, 1])

print database.getRatings("darylsew@gmail.com")
print database.getRatings("jpengsmail@gmail.com")
