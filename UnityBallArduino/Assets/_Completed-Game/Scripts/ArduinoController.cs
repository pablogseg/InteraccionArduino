 using UnityEngine;
 using System.Collections;
 using System.IO.Ports;
 
 public class ArduinoController : MonoBehaviour {


     SerialPort sp = new SerialPort("COM5", 9600);
     string cadena, newCadena;
     float [] valores;
     int posicion;
     public float angleX, angleY;

     

 
     void Start () {
        sp.Open ();
        sp.ReadTimeout = 1;       
        valores = new float [2];
        posicion = 0;
     }
 
     void Update () 
     {
         try{
            cadena = sp.ReadLine();
            posicion = 0;
            newCadena = "";           
           for (int i = 0; i < cadena.Length; i++){
                if (cadena[i] == '\t'&& newCadena != ""){
                    valores[posicion]= float.Parse(newCadena);
                    posicion ++;
                    newCadena ="";
                }
                else if (cadena[i]== '\n'){
                    break;
                } 
                else{
                    newCadena += cadena[i];
                }
            }
            valores[posicion]= float.Parse(newCadena);
         }
         catch(System.Exception){
         }

        angleX = valores[0]/90;
        angleY = valores[1]/90;

     }
 }