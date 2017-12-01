import java.io.*;
import java.net.*;

public class Server1{

public static void main(String []args) throws IOException{
ServerSocket s1=new ServerSocket(57122);
while(true){

Socket connectionsocket=s1.accept();
BufferedReader messagefromloadbalancer=new BufferedReader(new InputStreamReader(connectionsocket.getInputStream()));
String sentence=messagefromloadbalancer.readLine();
System.out.println("Received from client: "+sentence);
}
}
}
