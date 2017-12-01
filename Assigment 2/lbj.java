import java.net.*;
import java.io.*;

public class lbj{
public static void main(String []args) throws IOException{
ServerSocket s1=new ServerSocket(5712);
while(true){
Socket connectionsocket=s1.accept();
BufferedReader messagefromclient = new BufferedReader(new InputStreamReader(connectionsocket.getInputStream()));
String clientsentence=messagefromclient.readLine();

if(clientsentence.contains("server1")){
Socket server=new Socket("192.168.146.131",57122);
DataOutputStream outtoserver=new DataOutputStream(server.getOutputStream());
outtoserver.writeBytes(clientsentence+"\n");
server.close();
}

else if(clientsentence.contains("server2")){
Socket server2=new Socket("192.168.146.129",57123);
DataOutputStream outtoserver2=new DataOutputStream(server2.getOutputStream());
outtoserver2.writeBytes(clientsentence+"\n");
server2.close();
}
else{System.out.println("ERROR");}
}
}
}
