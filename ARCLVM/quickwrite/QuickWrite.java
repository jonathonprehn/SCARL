//default package

import java.io.*;

public class QuickWrite {

	public static void main(String[] args) {
		try {
			BufferedReader br = new BufferedReader(new FileReader("parseprocs.txt"));
			PrintWriter pw = new PrintWriter(new File("quickwrite_out.txt"));
			String str = null;
			int i = 0;
			while((str = br.readLine()) != null) {
				if (i > 0) {
					pw.print("else ");
				}
				pw.println("if (strcmp(\"" + str + "\", instruction_code) == 0) {");
				pw.println("\t");
				pw.println("}");
				
				i++;
			}
			pw.println("else {");
			pw.println("\t");
			pw.println("}");
			pw.flush();
			pw.close();
			br.close();
		} catch(IOException ioe) {
			System.err.println("IO ERROR: " + ioe);
		}
	}
}