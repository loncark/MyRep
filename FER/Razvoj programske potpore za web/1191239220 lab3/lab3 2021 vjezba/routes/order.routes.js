//(id, name, description, seasonal) u categories bazi
//(id, name, price, categoryid, imageurl, colors) u inventory bazi

const express = require("express");
router = express.Router();

const db = require('../db');

(async function() {
    var res = await db.query('SELECT * FROM categories');
    return res;
})()
.then(
    function(result){
        (async function() {
            var res = await db.query('SELECT * FROM inventory');
            return res;
        })()
        .then(
            function(result2){
                /* nemam pojma zasto tu ide / a ne /order */
                router.get('/', function(req, res, next){
                    res.render('../views/order', {
                        linkActive: 'order',
                        categories: result.rows,
                        inventory: result2.rows,
                        pageTitle: 'Order'
                    });
                });
            
            },
            function(error) {console.log(error);}
        ).catch(err => console.log(err))
    
    },
    function(error) {console.log(error);}
).catch(err => console.log(err))

module.exports = router;

