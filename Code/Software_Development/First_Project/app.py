from flask import Flask, render_template, request
import database
import shelve
import sys
import stat

app = Flask(__name__)
globalemail = ""

@app.route("/", methods = ["GET", "POST"])
def home():
    global globalemail
    """
    On the main page a user will type in their email and press the login button.
    This will lead them to a second page (choice.html).
    """
    error = ""
    if request.method == "POST":
        if valid_login(request.form['email'], request.form['IDnum']):
            globalemail = str(request.form['email'])
            return log_the_user_in()
        else:
            error = "Invalid username/password"

    return render_template("login.html", error=error)

@app.route("/choose/", methods = ["GET", "POST"])
def log_the_user_in():
    global globalemail
    """
    The user arrives at this page if they login successfully.
    Here, they can choose whether they want to a) see ratings or b) rate people.
    """
        
    return render_template("page.html")

@app.route("/rate/", methods = ["GET", "POST"])
def rate_page():
    global globalemail
    members = database.getGroupMembers(globalemail)
    auth = shelve.open("authen")
    members[0] = auth[members[0]][0] + " " + auth[members[0]][1]
    members[1] = auth[members[1]][0] + " " + auth[members[1]][1]
    members[2] = auth[members[2]][0] + " " + auth[members[2]][1]

    #assuming there are 3 members- this could be dynamic but that's slightly more difficult
    #I don't REALLY want to do any more work than I have to
    message = ""
    f = open("questions.txt", "r").readlines()
    q1 = f[0]
    q2 = f[1]
    q3 = f[2]
    q4 = f[3]
    if request.method == "POST":
        """
        print request.form['mem1q1']
        print request.form['mem1q2']
        print request.form['mem1q3']
        print request.form['mem1q4']
        print request.form['mem2q1']
        print request.form['mem2q2']
        print request.form['mem2q3']
        print request.form['mem2q4']
        print request.form['mem2q4']
        print request.form['mem3q1']
        print request.form['mem3q2']
        print request.form['mem3q3']
        print request.form['mem3q4']

        print "Member1 Question1 is null:"
        print request.form['mem1q1'] is None
        print "Member3 Question4 is null:"
        print request.form['mem3q4'] is None
        """

        try:
            mem1ratings = [request.form['mem1q1'], 
                           request.form['mem1q2'],
                           request.form['mem1q3'],
                           request.form['mem1q4']]
            
            mem2ratings = [request.form['mem2q1'],
                           request.form['mem2q2'],
                           request.form['mem2q3'],
                           request.form['mem2q4']]
            
            mem3ratings = [request.form['mem3q1'],
                           request.form['mem3q2'],
                           request.form['mem3q3'],
                           request.form['mem3q4']]
            
            database.addRating(globalemail, members[0], mem1ratings)
            database.addRating(globalemail, members[1], mem2ratings)
            database.addRating(globalemail, members[2], mem3ratings)
            message="Rated successfully!"
        except:
            message="You didn't answer every question."
        return render_template("rate.html",
                               ratername=auth[globalemail][0] + auth[globalemail][1],
                               mem1=members[0],
                               mem2=members[1],
                               mem3=members[2],
                               message=message,
                               q1=q1,
                               q2=q2,
                               q3=q3,
                               q4=q4)
    return render_template("rate.html",
                           ratername=auth[globalemail][0] + " " + auth[globalemail][1],
                           mem1=members[0],
                           mem2=members[1],
                           mem3=members[2],
                           message=message,
                           q1=q1,
                           q2=q2,
                           q3=q3,
                           q4=q4
                           )

@app.route("/ratings/", methods = ["GET", "POST"])
def ratings_page():
    global globalemail
    """
    I don't really feel like doing the thing Z talked about in class for this so I'll just hardcode stuff. Might do some fancy visualization stuff with d3.js if I have time and feel like it- this is pretty barebones.
    """
    f = open("questions.txt", "r").readlines()
    if len(database.getRatings(globalemail))==0:
        return render_template("ratings.html", q1="No ratings for you yet!")

    q1ans = ""
    q2ans = ""
    q3ans = ""
    q4ans = ""

    for rating in database.getRatings(globalemail):
        q1ans += str(rating[0]) + " "
        q2ans += str(rating[1]) + " "
        q3ans += str(rating[2]) + " "
        q4ans += str(rating[3]) + " "
    
    return render_template("ratings.html",
                           q1=f[0],
                           q1ans=q1ans,
                           q2=f[1],
                           q2ans=q2ans,
                           q3=f[2],
                           q3ans=q3ans,
                           q4=f[3],
                           q4ans=q4ans)

def valid_login(email, IDnum):
    auth = shelve.open("authen")
    valid = False
    try:
        valid = auth[str(email)][2] == IDnum
    except KeyError, e:
        return valid
    else:
        return valid

if __name__ == "__main__":
    app.run(port=7011)
