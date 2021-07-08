import java.io.*;

import javax.servlet.Servlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

import java.net.*;
import java.util.Scanner;

public class source implements Servlet {

	public String master_branch, local_branch, fclone;

	@Override
	public void destroy() {
		// TODO Auto-generated method stub
		System.out.println("In destroy");
	}

	@Override
	public ServletConfig getServletConfig() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public String getServletInfo() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void init(ServletConfig arg0) throws ServletException {
		// TODO Auto-generated method stub
		System.out.println("In init");
	}

	@Override
	public void service(ServletRequest request, ServletResponse response) throws ServletException, IOException {
		
		response.setContentType("text/html"); 
		PrintWriter pw = response.getWriter(); 
		pw.println("<h2>Cloning...</h2>");
		pw.close();
		System.out.println("In service");
		
		master_branch = request.getParameter("mbranch");
		local_branch = request.getParameter("lbranch");	
		fclone = request.getParameter("fclone");
		
		System.out.println("mb: " +master_branch);
		System.out.println("lb: " +local_branch);
		System.out.println("fc: " +fclone);
		
		int n;
		n = client();
		System.out.println(n);
	}
	
	public int client() throws IOException
	{

		Socket sock = new Socket("127.0.0.1",9250);

		//Receiving data
		Scanner sc1 = new Scanner(sock.getInputStream());
		String temp = sc1.nextLine();
		System.out.println(temp);

		BufferedWriter wr = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream())); 
		
		wr.write(master_branch);
		wr.flush();	
	 
		wr.write(local_branch +"\n");
		wr.flush();
		
		wr.write(fclone);
		wr.flush();
		
		String temp2 = sc1.nextLine();
		System.out.println(temp2);
		sock.close();
		
		return 1;
	}
}
