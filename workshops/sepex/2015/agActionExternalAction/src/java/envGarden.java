// Environment code for project agActionExternalAction

import jason.asSyntax.*;
import jason.environment.*;
import java.util.logging.*;

public class envGarden extends Environment {

    private Logger logger = Logger.getLogger("agActionExternalAction."+envGarden.class.getName());

    /** Called before the MAS execution with the args informed in .mas2j */
    @Override
    public void init(String[] args) {
        super.init(args);
    }

    @Override
    public boolean executeAction(String agName, Structure action) {
        if (action.getFunctor().equals("sniff")) {
        	logger.info("Spot sniffed by " + agName);
        }
        return true;
    }

    /** Called before the end of MAS execution */
    @Override
    public void stop() {
        super.stop();
    }
}
