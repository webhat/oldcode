import java.util.Vector;

class test {
				public test() {
								new Vector();
				}

				public static void main(String arg[]) {
								System.out.println("X");
								try {
												new test();
								} catch(Exception e) {
												e.printStackTrace();
								}
								System.out.println("X");
				}
}
