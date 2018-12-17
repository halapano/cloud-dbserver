class DBHandler {
  constructor(dbclient, dbName, collecitonName, fs) {
    this.client = dbclient;
    this.dbName = dbName;
    this.collecitonName = collecitonName;
  }

  // method to connect to the databse using client
  testconnect() {
    this.client.connect((err) => {
      if (err) {
        console.log(`testconnect() err: ${err}`);
        return;
      }
      console.log('Connected to the DB server');
      const db = this.client.db(this.dbName)
      // this.client.close()
    });
  }

  // method to get files
  get(callback) {
    return new Promise((resolve, reject) => {

      this.client.connect(async (err) => {
        if (err) {
          reject(err);
        } else {
          console.log('get() Connected to the mongo server');
          const db = this.client.db(this.dbName);
          const collection = db.collection(this.collecitonName);

          // due to the return type of collection.find()
          // is a Promise, it should be called as await expression
          const files = await collection.find({});
          console.log('dbHandler get() find() finished');
          await callback(files);
          resolve()
        }
      });
    });
  }

  // method to store a file
  store(file) {
    this.client.connect(async (err) => {
      if (err) {
        console.log(`store() -> connect() err: ${err}`);
        return;
      }
      console.log('Connected to the mongo server');
      const db = await this.client.db(this.dbName)
      const collection = await db.collection(this.collecitonName)

      collection.insertOne(file, (err) => {
        if (err) {
          console.log(`store() -> insertOne(): ${err}`);
        } else {
          console.log(`file ${file.filename} inserted!`);
        }
      });

    });
  }

  // method to delete a file
  delete(filename) {
    return new Promise((resolve, reject) => {
      this.client.connect((err) => {
        if (err) {
          reject(`dbHandler.delete() -> connect() err: ${err}`);
        }
        console.log('Connected to the DB server');
        const db = this.client.db(this.dbName)
        const deleteFilename = { filename: filename }

        db.collection(this.collecitonName).deleteOne(deleteFilename, (err) => {
          if (err) {
            reject(`dbHandler.delelte() -> deleteOne(): ${err}`);
          } else {
            console.log('file deleted!');
            resolve();
          }
        });

      });
    });
  }

  close() {
    this.client.close();
  }
}

module.exports = DBHandler;
