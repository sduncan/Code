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
        button = request.form["button"]
        if button == "Log Out":
            return redirect(url_for("home"))
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

if __name__ == "__main__":
    app.debug = True
    app.run(port=5001)
