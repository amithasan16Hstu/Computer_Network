import java.util.Random;

public class StopAndWaitProtocol {

    public static void main(String[] args) throws InterruptedException {
        int totalFrames = 10; 
        int frame = 0;       
        Random random = new Random();

        System.out.println("Stop-and-Wait Protocol Simulation\n");

        while (frame < totalFrames) {
            System.out.println("Sender: Sending frame " + frame + "...");
            simulateNetworkDelay();

           
            if (random.nextInt(100) < 70) { 
                System.out.println("Receiver: Frame " + frame + " received. Sending ACK...");
                simulateNetworkDelay();
                System.out.println("Sender: ACK for frame " + frame + " received.");
                frame++; 
            } else {
                System.out.println("Receiver: Frame " + frame + " received. ACK lost!");
                simulateNetworkDelay();
                System.out.println("Sender: Timeout for frame " + frame + ". Resending...");
            }
        }

        System.out.println("\nAll frames sent and acknowledged successfully!");
    }

    private static void simulateNetworkDelay() throws InterruptedException {
       
        Thread.sleep(500 + new Random().nextInt(1000));
    }
}
