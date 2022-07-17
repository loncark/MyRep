const express = require('express');
const { append } = require('express/lib/response');
const router = express.Router();
const User = require('../models/UserModel')
const db = require('../db')


router.get('/', function (req, res, next) {
    //####################### ZADATAK #######################
    //vrati login stranicu

    res.render('login', {
        title: 'Login',
        user: req.session.user,
        linkActive: 'login',
        err: undefined
    });

    //#######################################################

});

router.post('/', function (req, res, next) {
    //####################### ZADATAK #######################
    //postupak prijave korisnika
    //req.body je objekt {user, password}, res.body je undefined

    User.fetchByUsername(req.body.user)
    .then( 
        //fetchByUsername() result je objekt User (ispunjen ili prazan)
        function(result) { 
            if(result.user_name == undefined || 
                !result.checkPassword(req.body.password)) {
                res.render('login', {
                    title: 'Login',
                    user: req.session.user,
                    linkActive: 'login',
                    err: 'User does not exist or incorrect password.'
                });
            }
            else { /*       !!! NEPOTREBAN KOD !!!
                   PRIJE NEGO SE U REQ.SESSION USELI LOGIRANI USER I POHRANI
                   U BAZU, PREGLEDAJ BAZU ZA RETKOM KOJI U SESS VEC IMA TOG
                   USERA, AKA TIP JE VEC LOGIRAN U DRUGOM BROWSERU.

                (async function() {
                    var res = await db.query(`SELECT sid, sess FROM session;`);
                    return res;
                  })()
                  .then(
                      function(result2){
                        //result.rows je niz objekata {sid, sess{cookie,cart,?user?}}
                        for (let i=0; i < result2.rows.length; ++i) {
                          if(result2.rows[i].sess.user == result) {
                            req.sessionID = result2.rows[i].sid;
                            req.session.cookie = result2.rows[i].sess.cookie;
                            req.session.cart = result2.rows[i].sess.cart;
                          }
                        }
              
                      },
                      function(error) {console.log(error);}
                  ).catch(err => console.log(err));*/

                req.session.user = result;
                res.redirect('../');
            }
        },
        function(err) {console.log(err);}

    ).catch(err => console.log(err));
    
    

    //#######################################################

});


module.exports = router;