#!usr/bin/python

from pymongo import Connection

class db:
    def __init__(self):
        """ Handles connecting to mongo.stuycs.org, authentication, and connecting to our (Denis's/Sarah's) database. Returns our database.
        """
        self.connection = Connection('mongo.stuycs.org')
        self.db = self.connection.admin
        self.db.authenticate('ml7','ml7')
        self.db = self.connection['Denis_Sarah']
    
    
    def addStory(self, title):
        """ Given a title, adds a new story to database 
        """
        print self.db.stories.insert({'title':title,'lines':[]})
        
        
        
    def addLineToStory(self,title,line):
        """ Given a title and a line, adds the line to the story with that title.
        """
        self.db.stories.update( {'title': title}, {"$push": {"lines": line}})
            
    def removeAStory(self,title):
        """ Given a title, removes the story.
        """
        #collection = self.db.stories
        #storyTitle = [a for a in collection.find({"title" : title})][0]['title']
        self.db.stories.remove({'title': title})
        
            
    def removeStories(self):
        """ Removes all stories from the database
        """
        self.db.stories.drop()
            
            
    def returnStory(self,title=""):
        """ Given a title, returns the story
        """
        collection = self.db.stories
        try:
            answer = [a for a in collection.find({"title" : title})][0]['lines']
        except:
            answer = []
        return answer

    def returnTitles(self):
        collection = self.db.stories
        ans=[x["title"] for x in collection.find()]
        return ans

if __name__=="__main__":
    mydb = db()
    print mydb.db
    mydb.addStory("once upon a time");
    print mydb.returnTitles();
    print mydb.removeStories();
