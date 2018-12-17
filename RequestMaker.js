class RequestMaker {
  constructor(fs) {
    this.request = require('request');
    this.fs = fs;
  }

  get(url) {
    this.request.get({
      url: url
    }, (err, res) => {
      if (err) {
        console.log(`get(): ${err}`);
      } else {
        console.log('get() request made');
      }
    });
  }

  postOne(url, filepath, uploadName) {
    const r = this.request.post({
      url: url,
    }, (err, res, body) => {
      if (err) {
        console.log(err);
      } else {
        console.log('Request Maker: Request made');
      }
    });

    r.form().append(uploadName, this.fs.createReadStream(filepath));
  }

  postMany(url, filepath, uploadName) {
    return new Promise((resolve, reject) => {

        // read all filenames in filepath
        this.fs.readdir(filepath, async (err, fs) => {
          // form a list of filenames
          let allfiles = [];
          await fs.forEach((file) => {
            allfiles.push(this.fs.createReadStream(`${filepath}${file}`));
          });
          console.log(`length of allfiles: ${allfiles.length}`);
          console.log(`postMany() allfiles: ${allfiles}`);

          const formData = {
            files: allfiles
          }
          console.log(`postMany() formData: ${formData}`);

          this.request.post({
            url: url,
            formData: formData
          }, (err, res) => {
            if (err) {
              const er = `postMany() request.post(): ${err}`;
              reject(er);
            } else if (res.statusCode == 201){
              console.log('RequestMaker postMany made');
              resolve();
            } else {
              reject('No err and status code message');
            }

          });
        });
    });
  }
}

module.exports = RequestMaker;
