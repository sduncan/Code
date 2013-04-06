#!/usr/bin/python

from flask import Flask, request, render_template, url_for, flash, redirect

import utils
import urllib2

app = Flask(__name__)

global mydb

@app.route("/", methods = ['GET', 'POST'])
def home():
    mydb = utils.db()
    if request.method=='POST':
        button=request.form.get('button', None)
        new_story=request.form.get('new_story', "")
        selected=request.form.get('title', "")
        if button=="Choose story":
            url=urllib2.quote("/story/%s" %(selected))
            return redirect(url)
        if button=="Create story" and len(new_story)>0:
            mydb.addStory(new_story)
            return redirect("/")
        elif button=="Drop stories":
            mydb.removeStories()
            return redirect("/")

    titles = mydb.returnTitles()
    return render_template('template.html',titles=titles)

@app.route("/story/<title>", methods=['GET', 'POST'])
def story(title=""):
    mydb = utils.db()
    if request.method == 'GET':
        lines = mydb.returnStory(title)
        return render_template('storytemp.html', title=title, lines=lines)
    else:
        button=request.form.get('button', None)
        title=request.form.get('title', "")
        new_line=request.form.get('new_line', "")
        if button == 'Add':
            mydb.addLineToStory(title, new_line)
            return redirect("/story/%s" %(title))
        elif button == 'Delete':
            mydb.removeAStory(title)
            return redirect("/")
        else:
            return redirect("/")

if __name__=="__main__":
    app.run(debug=True, port=5000)
