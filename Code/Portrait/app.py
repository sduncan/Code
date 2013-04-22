from flask import Flask,render_template,request,url_for,redirect,flash,session

app = Flask(__name__)

@app.route('/',methods=["POST", "GET"])
def home():
    return render_template("home.html")

if __name__ == "__main__":
    app.debug = True
    app.run()
