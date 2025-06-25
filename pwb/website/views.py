from flask import Blueprint, render_template

views = Blueprint('views',__name__)

#homepage
@views.route('/')
#this func will run whenever we go to /
def home():
   return render_template("home.html")