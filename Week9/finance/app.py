import os

from cs50 import SQL
from flask import *
from flask import Flask, flash, redirect, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date
from datetime import datetime


from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    totalcashstocks = 0
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as shares, price FROM stocks WHERE userID = ? GROUP BY symbol HAVING (SUM(shares)) > 0;",
        session["user_id"],)

    infos = ""
    if stocks:
        for stock in stocks:
            quote = lookup(stock["symbol"])
            stock["name"] = quote["name"]
            stock["price"] = quote["price"]
            stock["total"] = round(stock["price"] * stock["shares"], 2)
            totalcashstocks = totalcashstocks + stock["total"]
    else:
        infos = "No stocks found!"

    totalcash = totalcashstocks

    totaltotalcash = totalcashstocks + cash[0]["cash"]

    return render_template("index.html", stocks=stocks, totalcash=totalcash, cash=cash[0]["cash"], infos=infos, totaltotalcash=totaltotalcash)


@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changepassword():

    if request.method == "POST":

        oldpw = request.form.get("oldpw")

        newpw = request.form.get("newpw")

        if ((not oldpw) or (not newpw)):
            return apology("Invalid pw!", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], oldpw):
            return apology("invalid username and/or password", 403)
        else:
            db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(newpw), session["user_id"])

        return redirect("/")

    else:
        return render_template("changepassword.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    # User reached route via POST (as by submitting a form via POST)

    if request.method == "POST":

        shares = 0
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("No valid shares!", 400)

        symbol = request.form.get("symbol")

        price = lookup(symbol)

        if not symbol or not price:
            return apology("No symbol!", 400)
        elif shares < 1:
            return apology("No valid shares!", 400)
        elif ((price["price"] * shares) > (db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"])):
            return apology("Not enought money!", 400)

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", (price["price"] * shares), session["user_id"],)

        alradyb = db.execute("SELECT userID FROM stocks WHERE userID = ? AND symbol = ?", session["user_id"], symbol.upper())

        print(str(session["user_id"]) + " " + symbol)
        print(alradyb)

        if not alradyb:
            db.execute("INSERT INTO stocks (userID, symbol, shares, price) VALUES (?, ?, ?, ?)",
                       session["user_id"], symbol.upper(), shares, price["price"])
        else:
            db.execute("UPDATE stocks SET shares = (shares + ?) WHERE symbol = ? AND userID = ?",
                       shares, symbol.upper(), session["user_id"])

        db.execute("INSERT INTO transactions (symbol, shares, price, transactiontype, date, time , userID) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   symbol.upper(), price["price"], shares, "buy", date.today(), datetime.now().strftime("%H:%M:%S"), session["user_id"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute(
        "SELECT * FROM transactions WHERE userID = ?",
        session["user_id"],)

    infos = ""
    if not transactions:
        infos = "No transactions found!"

    return render_template(
        "history.html", transactions=transactions, infos=infos)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "GET":

        return render_template("quote.html")
    else:
        quote = lookup(request.form.get("symbol"))

        if(quote):
            return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=quote["price"],)

        else:
            return apology("must provide valid symbol", 400)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        password1 = request.form.get("confirmation")

        if (name) and (password) and (password1) and (password == password1) and (len(db.execute("SELECT * FROM users WHERE username = ?", name)) == 0):
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, generate_password_hash(password))
        else:
            return apology("Password or Username dose not work!", 400)

        return redirect("/")

    else:

        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        shares = int(request.form.get("shares"))

        symbol = request.form.get("symbol")

        price = lookup(symbol)

        if not shares or not symbol:
            return apology("No symbol or shares!", 400)
        elif shares < 1 or shares > int(db.execute("SELECT shares FROM stocks WHERE userID = ? AND symbol = ?", session["user_id"], symbol)[0]["shares"]):
            return apology("No valid shares!", 400)

        db.execute("UPDATE stocks SET shares = (shares - ?) WHERE userID = ? AND symbol = ?", shares, session["user_id"], symbol,)

        sshares = db.execute("SELECT shares FROM stocks WHERE userID = ? AND symbol = ?", session["user_id"], symbol)

        if int(sshares[0]["shares"]) == 0:
            db.execute("DELETE FROM stocks WHERE userID = ? AND symbol = ?", session["user_id"], symbol)

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", shares * price["price"], session["user_id"],)

        db.execute("INSERT INTO transactions (symbol, price, shares, transactiontype, date, time , userID) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   symbol.upper(), price["price"], shares, "sell", date.today(), datetime.now().strftime("%H:%M:%S"), session["user_id"])

        return redirect("/")
    else:
        #currstock = db.execute("SELECT symbol FROM stocks WHERE userID = ? GROUP BY symbol", session["user_id"],)
        user_id = session["user_id"]
        stocks = []
        query = db.execute("SELECT symbol FROM stocks WHERE userID = ?", user_id)

        for q in query:
            symbol = q["symbol"]

            if symbol not in stocks:
                stocks.append(symbol)

        return render_template("sell.html", stocks=stocks)

