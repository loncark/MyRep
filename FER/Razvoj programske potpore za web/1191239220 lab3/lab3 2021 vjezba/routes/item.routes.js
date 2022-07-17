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
                (async function() {
                    var res = await db.query('SELECT * FROM experts');
                    return res;
                })()
                .then(
                    function(result3){
                        
                        router2.get('/:id([0-9]{1,2})', function(req, res, next){
                            let id = parseInt(req.params.id-1);
                            res.render('../views/item', {
                                 linkActive: 'item',
                                 item: result2.rows[id],
                                 category: result.rows[result2.rows[id].categoryid-1],
                                 pageTitle: result2.rows[id].name,
                                 experts: result3.rows
                            });
                         });
                         
                         router2.get('/:id([0-9]{1,2})/addexpert', function(req, res, next){
                            let id = parseInt(req.params.id-1);
                            res.render('../views/predlozak', {
                                 linkActive: 'item',
                                 item: result2.rows[id],
                                 category: result.rows[result2.rows[id].categoryid-1],
                                 pageTitle: 'Add Expert',
                                 experts: result3.rows
                            });
                         });

                         router2.post('/:id([0-9]{1,2})/addexpert', function(req, res, next){
                            //u req.body su pospremljeni podaci forme u obliku objekta
                            //omoguceno s app.use(express.urlencoded(...)) u server.js
                            
                            //treba ubaciti info u bazu podataka
                            (async function() {
                                var res = await db.query(
                                    "INSERT INTO experts (name, surname, email, employedsince, expertsince, expertfor) VALUES ('prva', 'druga', 'treca', 4, 5, 6);");
                                return res;
                            })()
                            .then(
                                function(result4){                                              
                                        //treba poslati nazad item stranicu s updateanom listom strucnjaka
                                        let id = parseInt(req.params.id-1);
                                        res.render('../views/item', {
                                            linkActive: 'item',
                                            item: result2.rows[id],
                                            category: result.rows[result2.rows[id].categoryid-1],
                                            pageTitle: 'Add Expert',
                                            experts: result3.rows
                                        });                                                   
                                                                   
                                    },
                                function(error) {console.log(error);}
                            ).catch(err => console.log(err))

                            
                         });
                    
                        },
                    function(error) {console.log(error);}
                ).catch(err => console.log(err))
            },
            function(error) {console.log(error);}
        ).catch(err => console.log(err))
    
    },
    function(error) {console.log(error);}
).catch(err => console.log(err));    

module.exports = router2;

