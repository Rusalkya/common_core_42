import { useNavigate } from 'react-router-dom'

const FONT = 'Gribouillit2.0, sans-serif'

const sectionStyle = {
  backgroundColor: 'white', border: '3px solid black',
  borderRadius: '4px', padding: '1.5rem', marginBottom: '1.25rem'
}

export default function TermsOfService() {
  const navigate = useNavigate()

  return (
    <div style={{ minHeight: '100vh', backgroundColor: '#f5f5f5', fontFamily: FONT, padding: '2rem 1rem' }}>
      <div style={{ maxWidth: '800px', margin: '0 auto' }}>

        <div style={{ ...sectionStyle, display: 'flex', alignItems: 'center', gap: '1rem' }}>
          <button
            onClick={() => navigate(-1)}
            style={{
              padding: '0.5rem 1rem', backgroundColor: 'white', color: '#000',
              border: '2px solid black', borderRadius: '4px',
              cursor: 'pointer', fontFamily: FONT, fontWeight: 'bold'
            }}
          >
            Retour
          </button>
          <h1 style={{ margin: 0, fontSize: '1.8rem', color: '#000' }}>
            Conditions d'utilisation
          </h1>
        </div>

        <div style={{ ...sectionStyle, fontSize: '0.85rem', color: '#666' }}>
          <p style={{ margin: 0 }}>Derniere mise a jour : mai 2026</p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>1. Acceptation des conditions</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            En creant un compte sur <strong>GribouilleIt</strong>, vous acceptez les presentes conditions
            d'utilisation dans leur integralite. Si vous n'acceptez pas ces conditions, veuillez ne pas
            utiliser le service.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>2. Description du service</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            GribouilleIt est une plateforme sociale creative permettant aux utilisateurs de creer et partager
            des dessins numeriques, d'interagir avec d'autres membres via un systeme de commentaires, de
            mentions "j'aime", de reposts, de messages prives et d'un chat en direct.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>3. Creation de compte</h2>
          <p style={{ color: '#333', lineHeight: 1.7, marginBottom: '0.75rem' }}>
            Pour utiliser GribouilleIt, vous devez creer un compte avec une adresse e-mail valide et un
            mot de passe securise. Vous vous engagez a :
          </p>
          <ul style={{ color: '#333', lineHeight: 1.9, paddingLeft: '1.5rem' }}>
            <li>Fournir des informations exactes lors de l'inscription.</li>
            <li>Maintenir la confidentialite de vos identifiants.</li>
            <li>Ne pas creer plusieurs comptes pour contourner une suspension.</li>
            <li>Etre l'unique responsable des actions effectuees depuis votre compte.</li>
          </ul>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>4. Contenu publie</h2>
          <p style={{ color: '#333', lineHeight: 1.7, marginBottom: '0.75rem' }}>
            Vous etes entierement responsable du contenu que vous publiez. Il est strictement interdit de publier :
          </p>
          <ul style={{ color: '#333', lineHeight: 1.9, paddingLeft: '1.5rem' }}>
            <li>Du contenu illegal, offensant, discriminatoire ou harcelant.</li>
            <li>Du contenu portant atteinte aux droits de propriete intellectuelle de tiers.</li>
            <li>Du contenu a caractere pornographique ou representant des mineurs de maniere inappropriee.</li>
            <li>Des informations personnelles d'autres utilisateurs sans leur consentement.</li>
            <li>Des logiciels malveillants, virus ou tout code nuisible.</li>
          </ul>
          <p style={{ color: '#333', lineHeight: 1.7, marginTop: '0.75rem' }}>
            GribouilleIt se reserve le droit de supprimer tout contenu non conforme et de suspendre
            les comptes en infraction.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>5. Propriete intellectuelle</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            Vous conservez tous les droits sur les dessins et contenus que vous creez. En publiant
            sur GribouilleIt, vous accordez a la plateforme une licence non exclusive et gratuite pour
            afficher votre contenu aux autres utilisateurs dans le cadre normal du service.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>6. Comportement des utilisateurs</h2>
          <p style={{ color: '#333', lineHeight: 1.7, marginBottom: '0.75rem' }}>
            Vous vous engagez a utiliser GribouilleIt de maniere respectueuse et a ne pas :
          </p>
          <ul style={{ color: '#333', lineHeight: 1.9, paddingLeft: '1.5rem' }}>
            <li>Harceler, menacer ou intimider d'autres utilisateurs.</li>
            <li>Tenter de contourner les mecanismes de securite de la plateforme.</li>
            <li>Utiliser des scripts automatises pour interagir avec le service sans autorisation.</li>
            <li>Surcharger intentionnellement les serveurs (attaque par deni de service).</li>
          </ul>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>7. Suspension et suppression de compte</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            GribouilleIt se reserve le droit de suspendre ou supprimer tout compte ne respectant pas ces
            conditions d'utilisation, sans preavis. Vous pouvez egalement supprimer votre propre compte
            a tout moment depuis la section "Zone de danger" de vos parametres.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>8. Limitation de responsabilite</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            GribouilleIt est fourni "tel quel" dans le cadre d'un projet pedagogique. La plateforme ne
            saurait etre tenue responsable des dommages directs ou indirects resultant de son utilisation,
            d'une interruption de service ou de la perte de donnees.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>9. Modifications des conditions</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            Ces conditions d'utilisation peuvent etre mises a jour. En continuant a utiliser GribouilleIt
            apres toute modification, vous acceptez les nouvelles conditions.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>10. Contact</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            Pour toute question concernant ces conditions d'utilisation, contactez l'equipe GribouilleIt
            via le depot du projet sur GitHub.
          </p>
        </div>

      </div>
    </div>
  )
}
