inputInjector = process.atomBinding('input_injector').inputInjector
EventEmitter = require('events').EventEmitter

powerMonitor.__proto__ = EventEmitter.prototype

module.exports = inputInjector
