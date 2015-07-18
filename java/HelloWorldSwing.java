package start;

    import javax.swing.*;

    public class HelloWorldSwing {
        public static void main(String[] args) {
            //Create and set up the window.
            JFrame frame = new JFrame("HelloWorldSwing");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            JLabel label = new JLabel("Hello World");
            frame.add(label);

            //Display the window.
            frame.pack();
            frame.setVisible(true);
        }
    }
    class Dummy {
        // just to have another thing to pack in the jar
    }
