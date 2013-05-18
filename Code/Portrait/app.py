from flask import Flask,render_template,request,url_for,redirect,flash,session

app = Flask(__name__)

@app.route('/',methods=["POST", "GET"])
def home():
    if request.method == "POST":
        button = request.form["button"]
        name = request.form["usern"]
        paswrd = request.form["userp"]
        if button == "Sign In":
            if name=='TrustedUser' and paswrd=='Enter':
                return redirect(url_for("main"))
    return render_template("home.html")

@app.route('/main',methods=["POST", "GET"])
def main():
    if request.method == "POST":
        image = request.form["pic"]
        button = request.form["button"]

        if button == "Log Out":
            return redirect(url_for("home"))
        if image == "goal":
            return redirect(url_for("goal"))
        if image == "music":
            return redirect(url_for("music"))
        if image == "bench":
            return redirect(url_for("bench"))
        if image == "baseball":
            return redirect(url_for("baseball"))
        if image == "code":
            return redirect(url_for("code"))
        if image == "rose":
            return redirect(url_for("rose"))
        if image == "bandana":
            return redirect(url_for("bandana"))

    return render_template("main.html")

@app.route('/goal',methods=["POST", "GET"])
def goal():
    if request.method == "POST":
        button = request.form["button"]
        if button == "Log Out":
            return redirect(url_for("home"))
        if button == "Main":
            return redirect(url_for("main"))
    return render_template("goal.html")

@app.route('/music',methods=["POST", "GET"])
def music():
    return render_template("music.html")

@app.route('/bench',methods=["POST", "GET"])
def music():
    return render_template("bench.html")

@app.route('/baseball',methods=["POST", "GET"])
def music():
    return render_template("baseball.html")

@app.route('/code',methods=["POST", "GET"])
def music():
    return render_template("code.html")

@app.route('/rose',methods=["POST", "GET"])
def music():
    return render_template("rose.html")

@app.route('/bandana',methods=["POST", "GET"])
def music():
    return render_template("bandana.html")

if __name__ == "__main__":
    app.debug = True
    app.run(port=5001)
