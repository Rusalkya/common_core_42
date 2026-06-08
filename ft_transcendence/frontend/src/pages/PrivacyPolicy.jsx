import { useNavigate } from 'react-router-dom'

const FONT = 'Gribouillit2.0, sans-serif'

const sectionStyle = {
  backgroundColor: 'white', border: '3px solid black',
  borderRadius: '4px', padding: '1.5rem', marginBottom: '1.25rem'
}

export default function PrivacyPolicy() {
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
            Politique de confidentialite
          </h1>
        </div>

        <div style={{ ...sectionStyle, fontSize: '0.85rem', color: '#666' }}>
          <p style={{ margin: 0 }}>Derniere mise a jour : mai 2026</p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>1. Introduction</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            Bienvenue sur <strong>GribouilleIt</strong>. Nous attachons une grande importance a la protection
            de vos donnees personnelles. Cette politique de confidentialite vous informe sur la maniere
            dont nous collectons, utilisons et protegeaons vos informations lorsque vous utilisez notre
            plateforme.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>2. Donnees collectees</h2>
          <p style={{ color: '#333', lineHeight: 1.7, marginBottom: '0.75rem' }}>
            Nous collectons uniquement les donnees necessaires au fonctionnement du service :
          </p>
          <ul style={{ color: '#333', lineHeight: 1.9, paddingLeft: '1.5rem' }}>
            <li><strong>Donnees de compte</strong> : adresse e-mail, nom d'utilisateur, mot de passe chiffre (bcrypt).</li>
            <li><strong>Contenu utilisateur</strong> : dessins publies, commentaires, biographie du profil.</li>
            <li><strong>Avatar</strong> : image de profil choisie lors de l'inscription ou mise a jour ulterieurement.</li>
            <li><strong>Donnees de connexion</strong> : date de creation du compte, derniere activite.</li>
            <li><strong>Messages</strong> : messages prives echanges avec d'autres utilisateurs, messages du chat global.</li>
          </ul>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>3. Utilisation des donnees</h2>
          <p style={{ color: '#333', lineHeight: 1.7, marginBottom: '0.75rem' }}>
            Vos donnees sont utilisees exclusivement pour :
          </p>
          <ul style={{ color: '#333', lineHeight: 1.9, paddingLeft: '1.5rem' }}>
            <li>Creer et gerer votre compte utilisateur.</li>
            <li>Afficher votre profil et vos publications aux autres utilisateurs.</li>
            <li>Permettre les interactions sociales (amis, messages, notifications).</li>
            <li>Assurer la securite et le bon fonctionnement de la plateforme.</li>
          </ul>
          <p style={{ color: '#333', lineHeight: 1.7, marginTop: '0.75rem' }}>
            Nous ne vendons, ne louons et ne partageons pas vos donnees personnelles avec des tiers
            a des fins commerciales.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>4. Securite des donnees</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            Nous mettons en oeuvre des mesures techniques pour proteger vos donnees :
          </p>
          <ul style={{ color: '#333', lineHeight: 1.9, paddingLeft: '1.5rem' }}>
            <li>Les mots de passe sont haches avec <strong>bcrypt</strong> avant stockage.</li>
            <li>Les communications entre votre navigateur et nos serveurs sont chiffrees via <strong>HTTPS (TLS)</strong>.</li>
            <li>L'authentification repose sur des <strong>tokens JWT</strong> a duree de vie limitee.</li>
            <li>L'acces aux donnees est controle par un systeme de permissions.</li>
          </ul>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>5. Vos droits (RGPD)</h2>
          <p style={{ color: '#333', lineHeight: 1.7, marginBottom: '0.75rem' }}>
            Conformement au Reglement General sur la Protection des Donnees (RGPD), vous disposez des droits suivants :
          </p>
          <ul style={{ color: '#333', lineHeight: 1.9, paddingLeft: '1.5rem' }}>
            <li><strong>Droit d'acces</strong> : consulter les donnees personnelles que nous detenons vous concernant.</li>
            <li><strong>Droit de rectification</strong> : modifier vos informations depuis la page de parametres.</li>
            <li><strong>Droit a l'effacement</strong> : supprimer votre compte et l'ensemble de vos donnees via la section "Zone de danger" des parametres.</li>
            <li><strong>Droit a la portabilite</strong> : exporter vos donnees sur demande.</li>
          </ul>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>6. Conservation des donnees</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            Vos donnees sont conservees aussi longtemps que votre compte est actif. Lors de la suppression
            de votre compte, l'ensemble de vos donnees personnelles (profil, publications, messages, relations)
            est definitivement supprime de nos bases de donnees.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>7. Cookies</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            GribouilleIt utilise uniquement le stockage local (<strong>localStorage</strong>) de votre navigateur
            pour conserver votre token d'authentification. Aucun cookie de tracage ou de publicite n'est utilise.
          </p>
        </div>

        <div style={sectionStyle}>
          <h2 style={{ fontSize: '1.2rem', marginBottom: '0.75rem' }}>8. Contact</h2>
          <p style={{ color: '#333', lineHeight: 1.7 }}>
            Pour toute question relative a cette politique ou pour exercer vos droits, vous pouvez
            contacter l'equipe GribouilleIt via le depot du projet sur GitHub.
          </p>
        </div>

      </div>
    </div>
  )
}
