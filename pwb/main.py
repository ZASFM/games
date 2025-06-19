from website import create_app

app = create_app()
if __name__ == '__main__':
   #debug true reruns program on each change
   app.run(debug=True)
   