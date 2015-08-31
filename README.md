jumphash
===================

A Fast, Minimal Memory, Consistent Hash Algorithm

page:http://arxiv.org/pdf/1406.2294v1.pdf

##Usage

```javascript
  var jumphash = require('jumphash')
  var location = jumphash(2333,16)
  assert(location >= 0);
  assert(location < 16);
```

## License

MIT