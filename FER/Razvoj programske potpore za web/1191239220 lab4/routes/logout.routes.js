const express = require('express');
const router = express.Router();
const Cart = require('../models/CartModel')

router.get('/', function (req, res, next) {
    //####################### ZADATAK #######################
    // - obrisati sadržaj košarice
    // - odjaviti registriranog korisnika iz sustava
    // - napraviti redirect na osnovnu stranicu

    req.session.user = undefined;
    req.session.cart = new Cart.createCart();
    res.redirect('../');

    //#######################################################

});

module.exports = router;