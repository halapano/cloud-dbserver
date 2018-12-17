// REQUIRES
const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');
const bodyParser = require('body-parser');
const MongoCilent = require('mongodb').MongoClient;
const DBHandler = require('./DBHandler');
const RequestMaker = require('./RequestMaker');

// CONSTS
// db consts
const dbName = 'cloud-project';
const dbURL = 'mongodb://localhost:27017'; // need to change if uses on platforms
const collectionName = 'UploadedFiles';
const client = new MongoCilent(dbURL);
const dbHandler = new DBHandler(client, dbName, collectionName, fs);
const Binary = require('mongodb').Binary;

// tsuru server consts
const tsuruServerUrl = 'http://localhost:5000/files';
const production_tsuruServerUrl = 'http://node.192.168.99.100.nip.io/';

const app = express();
const uploadPath = 'uploads/';
const fileSize = 16000 // 16MB
const uploadFilename = 'upload';
const temp = 'temp/'; // path to store files to be sent to other side
const tempUploadName = 'files'; // id of the postMany
const requestMaker = new RequestMaker(fs);

// multer settings - change the uploaded filename
const storage = multer.diskStorage({
  destination: function(req, file, cb) {
    cb(null, uploadPath)
  },
  filename: function(req, file, cb) {
    cb(null, file.originalname)
  }
})

const upload = multer({
  storage: storage,
  dest: uploadPath,
  limits: {
    // fileSize: fileSize
  }
}).single(uploadFilename);

// MIDDLEWARE
app.use(bodyParser.urlencoded({ extended: true }));


// method that finally get the order correct!!
function writeFiles(files) {
  return new Promise((resolve, reject) => {
    files.forEach((file) => {
      fs.writeFile(`${temp}${file.filename}`, file.file_data.buffer, (err) => {
        if (err) {
          console.log(`/files get() fs.write: ${err}`);
        } else {
          console.log(`file ${file.filename} written`);
        }
      });

    }).then(() => {
      resolve();
    }).catch((err) => {
      console.log(`writeFiles() err: ${err}`);
    });
  });
}

// REQUESTS HANDLES
app.get('/', (req, res) => {
  // remove the line below to test if the mongdb is working
  // dbHandler.testconnect();
  res.send('No UI presented');
})

// get files
app.get('/files', async (req, res) => {
  console.log('get()');

  // send files to the tsuru server
  // requestMaker.post(tsuruServerUrl, filepath, uploadFilename);
  dbHandler.get((files) => {
    writeFiles(files).then(() => {

      // if all files are written then post them to the tsuru server /files
      requestMaker.postMany(tsuruServerUrl, temp, tempUploadName)
        .then(() => {
          res.status(201).end();
          console.log('/files get() res code 201 sent');
          console.log('/files get() request finished');

        }).catch((err) => {
          console.log(err);
        });

    }).catch((err) => {
      console.log(`get() connection err: ${err}`);
    });
  });

});

// store a file
app.post('/files/add', (req, res) => {
  // status code 201 succed
  // status code 500 fails
  console.log(`/files req.files: ${req.files}`);
  upload(req, res, async (err) => {
    if (err instanceof(multer.MulterError)) {
      console.log(`Upload err: ${err}`);

      res.status(500).end();

    } else {
      console.log(req.file);
      res.status(201);

      res.end()

      // construct a file to store
      const data = await fs.readFileSync(`${uploadPath}${req.file.originalname}`);
      const bin = Binary(data);
      const file = await {
        filename: req.file.originalname,
        file_data: bin
      };
      console.log(`/files file: ${file}`);
      // store the file
      dbHandler.store(file);
    }
  });
});

// delete a file
app.post('/files/delete', (req, res) => {
  console.log('delete()');
  // status code 201 succed
  // status code 500 fails
  console.log(`/files/delete post() filename: ${req.body['filename']}`);
  const deleteFilename = req.body['filename'];
  dbHandler.delete(deleteFilename)
  .then(() => {
    console.log('dbHandler.delete() finished');

    // delete temp files
    const deleteTempFilepath = `${temp}${deleteFilename}`;
    fs.unlink(deleteTempFilepath, (err) => {
      if (err) {
        console.log(`/files/delete post() fs.unlink(): ${err}`);
      } else {
        // make a request and send existing files
      requestMaker.postMany(tsuruServerUrl, temp, tempUploadName)
        .then(() => {
          res.status(201).end();
          console.log('/files/delete post() res code 201 sent');
          console.log('/files/delete post() request finished');

        }).catch((err) => {
          console.log(err);
        });
      }
    });

  }).catch((err) => {
    console.log(`/files/delete post(): ${err}`);
  });
});

app.listen(() => {
  console.log(`DB Server started on port ${process.env.PORT}`);
});

const server = app.listen(process.env.PORT || 5001);
