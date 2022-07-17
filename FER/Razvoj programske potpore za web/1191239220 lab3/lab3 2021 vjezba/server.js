const express = require("express");
app = express();
path = require('path');

/*Omogucava ejs, tj isprepletanje koda i html-a*/
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

/*Omogucava automatsko posluzivanje sadrzaja u public folderu,
inace dobivamo raw html*/
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.urlencoded({extended:true}));

const homeRouter = require('./routes/home.routes');
const orderRouter = require('./routes/order.routes');
const itemRouter = require('./routes/item.routes');

/*mapira adrese odgovarajucim routerima koji posljedicno pozivaju 
odgovarajuce handler funkcije definirane u xyz.routes.js fileovima*/
app.use('/', homeRouter);
app.use('/order', orderRouter);
app.use('/item', itemRouter);

app.listen(3000);