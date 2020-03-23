import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from datetime import datetime
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, represents_int

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    #which stocks the user owns in which quantity
    dics = db.execute("SELECT symbol, name, SUM(shares) FROM history WHERE user_id = :id GROUP BY symbol", id = session["user_id"])

    #get amount of cash user has
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
    intcash = float(cash[0]['cash'])

    #get the price of each stock
    prices = []
    total_values = []

    for dic in dics:
        temporary_lookup = []
        temporary_lookup = lookup(dic['symbol'])
        prices.append(temporary_lookup['price'])
        total_values.append((temporary_lookup['price'] * (int(dic['SUM(shares)']))))

    portfolio = (sum(total_values) + intcash)

    return render_template("index.html", stocks = dics, price = prices, cash = intcash, value = total_values, portfolio = portfolio)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check if symbol is inputed/correct and if #shares is correct by being a positive integer
        if not request.form.get("symbol"):
            return apology("Missing symbol", 400)

        elif lookup(request.form.get("symbol")) is None:
            return apology("Invalid symbol", 400)

        elif not represents_int(request.form.get("shares")):
            return apology("Amount of share must be an integer", 400)

        elif not int(request.form.get(("shares"))) > 0:
            return apology("Amount of share must a positive integer", 400)

        #call lookup function to look at current share price

        looku = (lookup(request.form.get("symbol")))
        price = looku["price"]
        shares = int(request.form.get("shares"))
        time = datetime.now().strftime("%B %d, %Y %I:%M%p")

        #Odds are you’ll want to SELECT how much cash the user currently has in users.
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        intcash = float(cash[0]['cash'])


        if intcash >= (price * shares):
            #appends data to table
            db.execute("INSERT INTO history (symbol, name, price, shares, time, user_id) VALUES (:symbol, :name, :price, :shares, :time, :user_id)",
            symbol = looku["symbol"], name = looku["name"], price = price, shares = shares, time = time, user_id = session["user_id"])
            db.execute("INSERT INTO bought (symbol, name, price, shares, time, user_id) VALUES (:symbol, :name, :price, :shares, :time, :user_id)",
            symbol = looku["symbol"], name = looku["name"], price = price, shares = shares, time = time, user_id = session["user_id"])

            #update cash
            intcash = (intcash - (price * shares))
            db.execute("UPDATE users SET cash = :cash where id = :id", cash = intcash, id = session["user_id"])

        elif intcash <= (price * shares):
            return apology("Insufficient amount of cash", 400)

        flash('Bought!')
        # Redirect user to home page
        return redirect("/")

    #User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    #get needed data
    stocks = db.execute("SELECT symbol, shares, price, time FROM bought UNION ALL SELECT symbol, shares, price, time FROM sold ORDER BY TIME DESC ")

    #print the data to history directory
    return render_template("history.html", stocks = stocks)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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

    #User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check if symbol is inputed and correct
        if not request.form.get("symbol"):
            return apology("Missing symbol", 400)

        elif lookup(request.form.get("symbol")) is None:
            return apology("Invalid symbol", 400)

        looku = (lookup(request.form.get("symbol")))

        return render_template("quoted.html", name=looku["name"], sym= looku["symbol"], price= looku["price"])


    #User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    #User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

            # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Missing username", 400)

            # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Missing password", 400)

            # Make sure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password and confirmation do not match", 400)

        #submit user's input via POST to /register
        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = username, hash = hash)
        if not result:
                return apology("Username already existing in database", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        return redirect("/", 200)


    #User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    #User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check if symbol is inputed/correct and if #shares is correct by being a positive integer
        if not request.form.get("symbol"):
            return apology("Missing symbol", 400)

        elif lookup(request.form.get("symbol")) is None:
            return apology("Invalid symbol", 400)

        elif not represents_int(request.form.get("shares")):
            return apology("Amount of share must be an integer", 400)

        elif not int(request.form.get(("shares"))) > 0:
            return apology("Amount of share must a positive integer", 400)

        # Query database for stock in portfolio
        symbols = db.execute("SELECT symbol FROM history WHERE user_id = :user_id",
                          user_id = session["user_id"])
        # put symbols in a list and transform user input into capitalized letters
        looku = lookup(request.form.get("symbol"))
        symbol_usable = looku['symbol']
        symbol_list = []
        for symbole in symbols:
            symbol_list.append(symbole['symbol'])

        #loop to see if user possess the aforementioned stock
        if not any(symbol_usable in item for item in symbol_list):
            return apology("You currently do not own any shares", 400)


        #takes the actualised price of the stock
        price = looku['price']
        shares = int(request.form.get("shares"))
        total_value = price * shares

        #update cash in database
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
        user_id = session["user_id"])
        intcash = float(cash[0]['cash'])
        db.execute("UPDATE users SET cash = :cash where id = :id", cash = intcash + total_value, id = session["user_id"])

        #use counter and delete share of netflix from database while counter of deleter share is not equal to sum of shares
        share_db = db.execute("SELECT SUM(shares) FROM history WHERE user_id = :user_id and symbol = :symbold",
        user_id = session["user_id"], symbold = symbol_usable)
        sum_shares = int(share_db[0]['SUM(shares)'])
        time = datetime.now().strftime("%B %d, %Y %I:%M%p")

        #verify that user has enough share
        if sum_shares < shares:
            return apology("You currently do not own enough shares", 400)


        #while loop that update rows with more than 1 shares and when not any of those start erasing rows,
        for x in range(shares):
            if (db.execute("select shares FROM history WHERE user_id = :user_id and symbol = :symbold and shares > 1"
            , user_id = session["user_id"], symbold = symbol_usable)):

                tx = db.execute("select transaction_id FROM history WHERE user_id = :user_id and symbol = :symbold and shares > 1"
                , user_id = session["user_id"], symbold = symbol_usable)
                tx_id = tx[0]['transaction_id']
                db.execute("INSERT into sold (symbol, name, price, shares, time, user_id) VALUES (:symbold, :name, :price, :shares, :time, :user_id)"
                , symbold = symbol_usable, name = looku["name"], price = price, shares = -shares, time = time, user_id = session["user_id"])
                db.execute("UPDATE history SET shares = shares - :value where user_id = :user_id and symbol = :symbold and transaction_id = :tx_id"
                , symbold = symbol_usable, value = 1, user_id= session["user_id"], tx_id = tx_id)


            elif not (db.execute("select shares FROM history WHERE user_id = :user_id and symbol = :symbold and shares > 1",
                user_id = session["user_id"], symbold = symbol_usable)):

                tx = db.execute("select transaction_id FROM history WHERE user_id = :user_id and symbol = :symbold and shares = 1",
                user_id = session["user_id"], symbold = symbol_usable)
                tx_id = tx[0]["transaction_id"]
                db.execute("INSERT into sold (symbol, name, price, shares, time, user_id) VALUES (:symbold, :name, :price, :shares, :time, :user_id)"
                , symbold = symbol_usable, name = looku["name"], price = price, shares = -shares, time = time, user_id = session["user_id"])
                result = db.execute("DELETE FROM history where user_id = :user_id and symbol = :symbold and transaction_id = :tx_id"
                , symbold = symbol_usable, user_id= session["user_id"], tx_id = tx_id)

        flash('Sold!')
        # Redirect user to home page
        return redirect("/")

    #User reached route via GET (as by clicking a link or via redirect)
    else:
        # Query database for stock in portfolio
        symbols = db.execute("SELECT symbol FROM history WHERE user_id = :user_id",
                          user_id = session["user_id"])
        return render_template("sell.html", symbols = symbols)

def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
