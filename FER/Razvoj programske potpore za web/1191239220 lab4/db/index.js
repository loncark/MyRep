const {Pool} = require('pg');

const pool = new Pool({
    user: 'USER',//'postgres',
    host: 'localhost',
    database: 'USER',
    password: 'password',
    port: 5432,
});

module.exports = {
    query: (text, params) => {
        const start = Date.now();
        return pool.query(text, params)
            .then(res => {
                const duration = Date.now() - start;
                //console.log('executed query', {text, params, duration, rows: res.rows});
                return res;
            });
    },
    pool: pool
}
