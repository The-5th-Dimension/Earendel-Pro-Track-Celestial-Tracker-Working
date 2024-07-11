// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";
//import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyDu7lDnpzXtNArNY5vuY2CnsuP20vwq6C0",
  authDomain: "earendeldb-bb3da.firebaseapp.com",
  databaseURL: "https://earendeldb-bb3da-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "earendeldb-bb3da",
  storageBucket: "earendeldb-bb3da.appspot.com",
  messagingSenderId: "211681728005",
  appId: "1:211681728005:web:b3f9090cdca8af94d52e6c",
  measurementId: "G-G0T3BGK9F4"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

export { app, db };
//const analytics = getAnalytics(app);