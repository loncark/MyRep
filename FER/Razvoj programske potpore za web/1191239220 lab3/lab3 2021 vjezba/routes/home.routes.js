const express = require("express");
router = express.Router();

homeHandler = function(req, res, next){
    res.render('../views/home', {
        linkActive: 'home',
        pageTitle: 'Home'
    });
};

router.get('/', homeHandler);

module.exports = router;