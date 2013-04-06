from flask import Flask,render_template,request,url_for,redirect,flash,session

app = Flask(__name__)

@app.route('/',methods=["POST","GET"])
def index():
    return render_template("creator.html")

if __name__ == "__main__":
    app.debug = True
    app.run()
    
