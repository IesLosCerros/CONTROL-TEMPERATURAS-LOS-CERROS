String StringFecha(time_t  t){
      String Fecha = FormatoHora(day(t))+ "/"+ FormatoHora(month(t))+ "/"+ FormatoHora(year(t))+ "  "
      +FormatoHora(hour(t))+ ":"+ FormatoHora(minute(t))+ ":"+ FormatoHora(second(t))+"              ";
      
      return(Fecha);     
   }

String FormatoHora(int dato){
  if (dato < 10){
    return("0"+String(dato));
    } 
  else{return(String(dato));}
  }

  long horaEntera(time_t  t){
    
    
    long horaEntera;
    horaEntera = hour(t)*100+ minute(t);
    return horaEntera;
    
    } 

    
void printFecha(time_t  t)
   {
       Serial.print(day(t)) ;    Serial.print(+ "/") ;   Serial.print(month(t));   Serial.print(+ "/") ;
       Serial.print(year(t));    Serial.print( " ") ;
       Serial.print(hour(t));   Serial.print(+ ":") ;   Serial.print(minute(t));   Serial.print(":") ;
       Serial.println(second(t));
       
   }

 // // el navegador envia HORA_SISTEMA=2017-11-19T09%3A53%3A10
void horaSistema2(String cabecera){  //  pone en hora el sistema al recibir la hora por internet
     
      if (request.indexOf(cabecera)!= -1){
      int index = request.indexOf(cabecera) + cabecera.length();
     
      
    String  hora = request.substring(index+11, index+13);
     String  minuto = request.substring(index+16, index+18);
    String  segundo = request.substring(index+21, index+23);
    String  dia = request.substring(index+8, index+10);
   String  mes = request.substring(index+5, index+7);
   String  ano = request.substring(index, index + 4);
  
    if (ano.toInt()>=2017){
    setTime(hora.toInt(),minuto.toInt(),segundo.toInt(),dia.toInt(),mes.toInt(),ano.toInt());


 }
// Send date over serial connection
 
  
 
      }
    
    } 


String enviarHORASISTEMA(){

  String cadena = "HORA_SISTEMA=" + formatohoralarga(hour())+formatohoralarga(minute())+formatohoralarga(second())+
  formatohoralarga(day())+formatohoralarga(month())+String(2000+year()-30);
   Serial.println(cadena); 
  return cadena;
  
  
  }    

String formatohoralarga( int dato){
  String salida;
  if(dato < 10){salida = "0" + String(dato);}
  else {salida = String(dato);}
  return salida;
  
  }


