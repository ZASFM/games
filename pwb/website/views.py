from flask import Blueprint

views = Blueprint('views',__name__)

#homepage
@views.route('/')
#this func will run whenever we go to /
def home():
   return "<h1>Test</h1>"