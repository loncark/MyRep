//(id, name, description, seasonal) u categories bazi
//(id, name, price, categoryid, imageurl, colors) u inventory bazi

const express = require("express");
router2 = express.Router();

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
                router2.get('/:id([0-9]{1,2})', function(req, res, next){
                    let id = parseInt(req.params.id-1);
                    res.render('../views/item', {
                         linkActive: 'item',
                         item: result2.rows[id],
                         category: result.rows[result2.rows[id].categoryid-1],
                         pageTitle: result2.rows[id].name
                    });
                 });},
            function(error) {console.log(error);}
        ).catch(err => console.log(err))
    
    },
    function(error) {console.log(error);}
).catch(err => console.log(err));    

module.exports = router2;