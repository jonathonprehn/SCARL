//default package

import java.io.*;

public class QuickWrite {

	public static void main(String[] args) {
		try {
			BufferedReader br = new BufferedReader(new FileReader("parseprocs.txt"));
			PrintWriter pw = new PrintWriter(new File("quickwrite_out.txt"));
			String str = null;
			while((str = br.readLine()) != null) {
				String modified = str.substring(0, str.length()-1);
				String procName = str.substring(
					str.indexOf("Parse"),
					str.indexOf("(") 
				);
				modified += (" is\n\tbegin\n\t\tnull;\n\tend " + procName + ";\n");
				pw.println(modified);
			}
			pw.flush();
			pw.close();
			br.close();
		} catch(IOException ioe) {
			System.err.println("IO ERROR: " + ioe);
		}
	}
}