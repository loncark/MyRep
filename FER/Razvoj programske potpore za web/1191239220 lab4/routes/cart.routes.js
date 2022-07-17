const express = require('express');
const router = express.Router();
const Cart = require('../models/CartModel')
const cartSanitizer = require('./helpers/cart-sanitizer');

// Ulančavanje funkcija međuopreme
router.get('/', cartSanitizer, function (req, res, next) {
    //####################### ZADATAK #######################
    // prikaz košarice uz pomoć cart.ejs

    res.render('cart', {
        title: 'Cart',
        user: req.session.user,
        linkActive: 'cart',
        err: undefined,
        cart: req.session.cart
    });

    //#######################################################
});


router.get('/add/:id', function (req, res, next) {
    //####################### ZADATAK #######################
    //dodavanje jednog artikla u košaricu
    
    Cart.addItemToCart(req.session.cart, req.params.id, 1)
    .then(
        function(result) {
            res.sendStatus(200);
        },
        function(error) {
            console.log(err);
            res.sendStatus(550);
        }
    ).catch(
        function(error) {
            console.log(err);
            res.sendStatus(560);
        }
    );

    //#######################################################
});

router.get('/remove/:id', function (req, res, next) {
    //####################### ZADATAK #######################
    //brisanje jednog artikla iz košarice

    Cart.removeItemFromCart(req.session.cart, req.params.id, 1)
    .then(
        function(result) {
            res.sendStatus(200);
        },
        function(error) {console.log(err);}
    ).catch(err => console.log(err));

    //#######################################################
});

module.exports = router;