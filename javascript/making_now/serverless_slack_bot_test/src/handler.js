'use strict';
const client = {
    id: process.env.CLIENT_ID,
    secret: process.env.CLIENT_SECRET
};

module.exports.hello = (event, context, callback) => {
  const response = {
    statusCode: 200,
    body: JSON.stringify({
      text: ["```",require('util').inspect(event,false,null),"```"].join("\n")
    })
  };
  console.log(process.env.CLIENT_ID);
  callback(null, response);
}

