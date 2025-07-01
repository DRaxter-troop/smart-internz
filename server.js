const express = require('express');
const app = express();
const port = process.env.PORT || 3000;

app.use(express.json());

// In-memory parking data
let parkingData = {
  slot1: false,
  slot2: true,
  user1: null,
  user2: "Abcd",
  vehiclesEntered: 1,
  vehiclesExited: 0,
  message: ""
};

app.get('/api/parking', (req, res) => {
  res.json(parkingData);
});

app.post('/api/parking', (req, res) => {
  const { slot1, slot2, vehiclesEntered, vehiclesExited, user, checkIn, slot, message } = req.body;

  // Update parking status
  parkingData.slot1 = slot1;
  parkingData.slot2 = slot2;
  parkingData.vehiclesEntered = vehiclesEntered;
  parkingData.vehiclesExited = vehiclesExited;

  if (user && checkIn && slot > 0) {
    if (slot === 1) parkingData.user1 = user;
    if (slot === 2) parkingData.user2 = user;
  } else if (user && !checkIn && slot > 0) {
    if (slot === 1) parkingData.user1 = null;
    if (slot === 2) parkingData.user2 = null;
  }

  if (message) parkingData.message = message;

  res.json(parkingData);
});

app.listen(port, () => {
  console.log(`Server running on port ${port}`);
});