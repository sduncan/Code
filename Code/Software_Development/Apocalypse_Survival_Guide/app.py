from flask import Flask, render_template, request, redirect, url_for, jsonify
from api import getAddress, getNearby, isPOI, distanceFrom, durationTo, getNearby

app = Flask(__name__)
global _name

@app.route("/", methods = ["GET", "POST"])
def home():
    if request.method == "GET":
        return render_template("index.html")

@app.route("/get_Address")
def get_Address():
    a = request.args.get('a', 0)
    return jsonify(result=getAddress(a))


@app.route("/distance_From")
def distance_From():
    o = request.args.get('o',"")
    d = request.args.get('d',"")
    m = request.args.get('m',"")
    return jsonify(result=distanceFrom(o,d,m))

@app.route("/duration_To")
def duration_To():
    o = request.args.get('o',"")
    d = request.args.get('d',"")
    m = request.args.get('m',"")
    return jsonify(result=durationTo(o,d,m))

@app.route("/get_Nearby")
def get_Nearby():
    r = request.args.get('r',5000)
    t = request.args.get('t',"")
    o = request.args.get('o',"345 Chambers Street, New York, NY, United States")
    return jsonify(result=getNearby(r,t,o))

if __name__ == "__main__":
    app.run(debug=True,host='0.0.0.0',port=7207)

    
