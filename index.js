var jump = require('./build/Release/jumphash');

module.exports = function wrapper(key, buckets){
    return jump.jumphash(key, buckets);
};
