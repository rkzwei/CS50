import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from datetime import datetime, timezone
from werkzeug.security import check_password_hash, generate_password_hash

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
    own = owned()
    portfolio = 0
    for share, amount in own.items():
        result = lookup(share)
        name, price = result["name"], result["price"]
        value = amount * price
        portfolio += value
        own[share] = (name, amount, usd(price), usd(value))
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]['cash']
    portfolio += cash
    return render_template("index.html", own=own, cash=usd(cash), portfolio=usd(portfolio))

    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    result = lookup(request.form.get("symbol"))
    if not result:
        return apology("Invalid Share Input")
    try:
        amount = int(request.form.get("shares"))
    except:
        return apology("Invalid input")
    if amount <= 0:
        return apology("Invalid number of shares")
    user_id = session["user_id"]
    transaction_price = (result["price"])*amount
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    check = cash - transaction_price
    if check < 0:
        return apology("Cannot afford transaction")
    """Buy shares of stock"""
    db.execute("UPDATE users SET cash = ? WHERE id = ?", check, user_id)
    db.execute("INSERT INTO orders (username, share, price_of_share, amount, date)\
        VALUES (?, ?, ?, ?, ?)", user_id, result["symbol"], result["price"], amount, time())
    return redirect("/")


@app.route("/history")
@login_required
def history():
    rows = db.execute("SELECT share, amount, price_of_share, date FROM orders WHERE username = ?", session["user_id"])
    return render_template("history.html", rows=rows)
    """Show history of transactions"""
    return apology("TODO")


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
    if request.method == "GET":
        return render_template("quote.html", alert=0)
    symbol = request.form.get("symbol")
    quoted = lookup(symbol)
    try:
        name = quoted["name"]
        price = usd(quoted["price"])
        symbol = quoted["symbol"]
    except:
        return apology("Invalid query")
    return render_template("quoted.html", name=name, price=price, symbol=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    username = request.form.get("username")
    password = request.form.get("password")
    confirm = request.form.get("confirmation")
    if username == "" or len(db.execute('SELECT username FROM users WHERE username = ?', username)) > 0:
        return apology("Username already exists or blank")
    if password != confirm or password == "":
        return apology("Password does not match or is blank")
    db.execute('INSERT INTO users (username, hash) \
        VALUES(?, ?)', username, generate_password_hash(password))
    query = db.execute('SELECT * FROM users WHERE username = ?', username)
    session.clear()
    session['user_id'] = query[0]["id"]
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    own = owned()
    if request.method == "GET":
        return render_template("sell.html", own=own.keys())
    result = lookup(request.form.get("symbol"))
    if not result:
        return apology("Invalid Share Input")
    amount = int(request.form.get("shares"))
    if amount <= 0:
        return apology("Invalid number of shares")
    if own[result["symbol"]] < amount:
        return apology("You do not own enough shares to sell")
    user_id = session["user_id"]
    transaction_price = (result["price"]) * amount
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    check = cash + transaction_price
    db.execute("UPDATE users SET cash = ? WHERE id = ?", check, user_id)
    db.execute("INSERT INTO orders (username, share, price_of_share, amount, date)\
        VALUES (?, ?, ?, ?, ?)", user_id, result["symbol"], result["price"], -amount, time())
    return redirect("/")


def owned():
    user_id = session["user_id"]
    own = {}
    search = db.execute("SELECT share, amount FROM orders WHERE username = ?", user_id)
    for i in search:
        share, amount = i["share"], i["amount"]
        own[share] = own.setdefault(share, 0) + amount
    own = {j: k for j, k in own.items() if k != 0}
    return own


def time():
    utc = datetime.now(timezone.utc)
    return str(utc.date()) + ' @time ' + utc.time().strftime("%H:%M:%S")