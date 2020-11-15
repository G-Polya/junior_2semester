var assert = require('assert');
var jsdom = require('mocha-jsdom');

global.document = jsdom();

describe('Mutliply', function() {
  var test = require('../index.js');  // late import
  it('should equal 9 when multiply is called', function() {
    assert.equal(9, test.multiply());
  });
});